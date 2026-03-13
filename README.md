# CPU5-ToolChain
The complet Tool chain for CPU5 include C compiler, ASM compiler and UART flasher

## How to use 
Modifie your flash pinout for your MCU and flash the firmware located at :

ToolchainCPU5/lasher3.1/MCU_flasher/MCU_flasher.ino

*This programe has been tested on ESP32 and Arduino uno but is compatible with every arduino compatible microcontrollers

Create a main.c near the toolchain file.

Open a terminal, type cd ToolchainCPU5/

If you are on linux, modify the Makefile with your path to files and type make or ./CompilCommande.bat {output_file_name_no_extension} {input_file_name.c} on windows
