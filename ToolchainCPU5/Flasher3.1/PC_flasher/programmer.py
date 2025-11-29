from time import sleep
import serial
import serial.tools.list_ports
import importlib.util
import sys
import os

def load_code_module(path):
    """Charge dynamiquement un module Python depuis un chemin."""
    module_name = os.path.splitext(os.path.basename(path))[0]

    spec = importlib.util.spec_from_file_location(module_name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

# ====================
#  Constants
# ====================


PORT = "/dev/ttyUSB0"

GET_ID     = 0x30
GET_PAGE   = 0x31
SET_PAGE   = 0x32
SET_ADDR   = 0x33
SEC_ERASE  = 0x34

VERBOSITY  = 0
Start_Adr  = 0x00001000

# ====================
#  Utility Functions
# ====================

def read_exact(ser, size):
    """Read exactly 'size' bytes or return what is available."""
    data = b""
    while len(data) < size:
        chunk = ser.read(size - len(data))
        if not chunk:
            break
        data += chunk
    return data


def printData(data, length, Address):
    """Pretty-print hexadecimal data by 16-byte rows."""
    if data is None:
        print("No data to print.")
        return

    for offset in range(0, length, 16):
        line = data[offset:offset + 16]
        addr = Address + offset
        print(f"0x{addr:04X} : " + " ".join(f"{b:02X}" for b in line))


# ====================
#  Arduino Commands
# ====================

def getId(ser):
    ser.reset_input_buffer()
    ser.write(bytes([GET_ID]))

    ack = ser.read(1)
    if ack == b'\x15':
        print("ERROR: GET_ID -> NACK")
        return None
    if ack != b'\x06':
        print("ERROR: GET_ID -> Timeout / Invalid ACK :", ack)
        return None

    data = read_exact(ser, 3)
    if len(data) != 3:
        print("ERROR: GET_ID -> Missing data")
        return None

    if VERBOSITY:
        print("ID:", [f"{b:02X}" for b in data])

    print(f"Flash memory : {data[2]} Mbits")
    return data


def setAddr(ser, addr):
    ser.reset_input_buffer()
    ser.write(bytes([SET_ADDR]))

    ack = ser.read(1)
    if ack == b'\x15':
        print("ERROR: SET_ADDR -> NACK")
        return None
    if ack != b'\x06':
        print("ERROR: SET_ADDR -> Timeout / Invalid ACK :", ack)
        return None

    ser.write(addr.to_bytes(4, "big"))
    if VERBOSITY:
        print(f"Adresse envoyée : 0x{addr:08X}")

    return True


def secErase(ser, addr):
    ser.reset_input_buffer()

    # align to sector
    sector_addr = addr & ~0xFFFF
    setAddr(ser, sector_addr)

    ser.write(bytes([SEC_ERASE]))
    ack = ser.read(1)

    if ack == b'\x15':
        print("ERROR: SEC_ERASE -> NACK")
        return None
    if ack != b'\x06':
        print("ERROR: SEC_ERASE -> Timeout / Invalid ACK :", ack)
        return None

    if VERBOSITY:
        print(f"Sector erased: 0x{sector_addr:08X}")

    return True


def getPage(ser):
    ser.reset_input_buffer()
    ser.write(bytes([GET_PAGE]))

    ack = ser.read(1)
    if ack == b'\x15':
        print("ERROR: GET_PAGE -> NACK")
        return None
    if ack != b'\x06':
        print("ERROR: GET_PAGE -> Timeout / Invalid ACK :", ack)
        return None

    data = read_exact(ser, 256)
    if len(data) != 256:
        print("ERROR: GET_PAGE -> Missing data")
        return None
    return data


def setPage(ser, page_data):
    """Send 0–256 bytes padded to 256 bytes."""
    ser.reset_input_buffer()
    ser.write(bytes([SET_PAGE]))

    ack = ser.read(1)
    if ack == b'\x15':
        print("ERROR: SET_PAGE -> NACK")
        return None
    if ack != b'\x06':
        print("ERROR: SET_PAGE -> Timeout / Invalid ACK :", ack)
        return None

    formatted = page_data.ljust(256, b'\x00')
    ser.write(formatted)

    return True


# ====================
#  Multi-page Write
# ====================

def writeMultiplePages(ser, address, data, length):
    if VERBOSITY:
        print("Starting multi-page writing.")
    else:
        print("Uploading...")

    written = 0

    # erase first sector
    secErase(ser, address)

    while written < length:
        curr = address + written

        # check for new sector
        if (curr & ~0xFFFF) != (address & ~0xFFFF):
            secErase(ser, curr)

        page_offset = curr & 0xFF
        space = 256 - page_offset
        chunk = min(space, length - written)

        if VERBOSITY:
            print(f"  Page: {chunk} bytes @ 0x{curr:08X}")

        setAddr(ser, curr)

        src_chunk = data[written:written + chunk].ljust(256, b'\x00')
        setPage(ser, src_chunk)

        # verification
        read_back = getPage(ser)

        if VERBOSITY:
            print("Page read:")
            printData(read_back, 256, curr)

        if read_back != src_chunk:
            print("ERROR: Verification failed!")
            return None

        written += chunk

        # progress bar
        if not VERBOSITY:
            percent = written * 100 / length
            bar = int(written * 50 / length)
            print(f"    {percent:.1f}% [{'#'*bar}{'.'*(50-bar)}]", end='\r')

    print(f"\nTotal written: {written} Bytes")
    return True


# ====================
#  MAIN
# ====================

def main():
    global PORT
    if len(sys.argv) < 2:
        print("Usage: programmer.py <prog.py>")
        return

    prog_path = sys.argv[1]
    prog_module = load_code_module(prog_path)

    code = prog_module.code

    while(1):
        try:
            ser = serial.Serial(PORT, baudrate=115200, timeout=2)
            break
        except:
            ports = list(serial.tools.list_ports.comports())
            if not ports:
                print("NO COM port found.")
            else:
                print("COM port found :")
                for p in ports:
                    print(p.device)
                PORT = input("Select your COM port >")


    print("Port selected :", ser.portstr)
    sleep(0.1)
    
    getId(ser)
    writeMultiplePages(ser, Start_Adr, code, len(code))
    sleep(0.1)

    print("Flashing finished.")
    ser.close()


if __name__ == "__main__":
    main()
