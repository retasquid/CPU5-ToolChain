#include"Clib/lib/Arduino.h"
#include"Clib/lib/shell.h"


int main(){
    char message_in[128];
    Serialbegin(0x117, 0x9ECA);
    GPO1 = 6;
    int d = 0x02;
    SerialPrintln("    ---- CPU5.9 Terminal ---- ");
    while(1){
        SerialPrint("cpu5_9>");
        SerialRead(&message_in, 128);
        command_decode(&message_in);
        SerialPrint("\n\r");
    }
}