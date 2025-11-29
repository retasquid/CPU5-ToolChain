#include"lib/Arduino.h"

int main(){
    Serialbegin(0x3C, 0x65E2); //115200 bps at 125MHz

    while(1){
        GPO0 = 5;
        char message_in[100];
        SerialPrintln("hello world!!!!!!!!");
        SerialRead(message_in, 100);
    }
}