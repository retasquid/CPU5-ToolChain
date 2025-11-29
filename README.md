# CPU5-ToolChain
The complet Tool chain for CPU5 include C compiler, ASM compiler and UART flasher

## How to use 
Modifie your flash pinour for your MCU and flash the firmware located at :

ToolchainCPU5/lasher3.1/MCU_flasher/MCU_flasher.ino

*This programe has been tested only on ESP32

Create a main.c near the toolchain file.

Open a terminal, type cd ToolchainCPU5/

If you are on linux, type make or ./CompilCommande.bat on windows
