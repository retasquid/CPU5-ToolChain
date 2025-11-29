#ifndef ARDUINO_H
#define ARDUINO_H

#define CLOCK_HZ_H 1   //0x9 
#define CLOCK_HZ_L 0x86A0//0xC018
#define CLOCK_KHZ 100    //639
#define CLOCK_MHZ 0

#define HIGH 1
#define LOW 0

// phase_inc = (baud * 2^32) / CLK_FREQ
// 0x3C 0x65E2 for 115200 bps at 125MHz
#define Serialbegin(incH, incL) BAUDH=incH; \
    BAUDL=incL

void delay_s(int seconds_delay){
    while(seconds_delay){
        int secdelay = CLOCK_HZ_H;
        while(secdelay){
            int cnt_delay = 9300;
            while(cnt_delay)cnt_delay--;
            secdelay--;
        }
        secdelay = CLOCK_HZ_L>>3;
        while(secdelay){
            secdelay--;
        }
        seconds_delay--;
    }
    return 0;
}

void delay_ms(int ms_delay){
    while(ms_delay){
        int msecdelay = CLOCK_KHZ>>3;
        while(msecdelay){
            msecdelay--;
        }
        ms_delay--;
    }
    return 0;
}

void SerialPrint(char* message_SerialPrint){
    int delay_i;
    for(int SerialPrint_i = -1; message_SerialPrint[SerialPrint_i+1];SerialPrint_i++){
        delay_i = 0;
        UART = message_SerialPrint[SerialPrint_i]|0x100;
        while(STATUS&0x02){delay_i++;}
        UART &= 0xFF;
        while(delay_i){delay_i--;}
    }
    return 0;
}

void SerialPrintln(char* messageln0){
    int delayln_i;
    for(int SerialPrintln_i = -1; messageln0[SerialPrintln_i+1]; SerialPrintln_i++){
        delayln_i = 0;
        UART = messageln0[SerialPrintln_i]|0x100;
        while(STATUS&0x02){delayln_i++;}
        UART &= 0xFF;
        while(delayln_i){delayln_i--;}
    }
    UART = 0x10a;
    delayln_i = 0;
    while(STATUS&0x02){delayln_i++;}
    UART = 0xa;
    while(delayln_i){delayln_i--;}
    UART = 0x10d;
    delayln_i = 0;
    while(STATUS&0x02){delayln_i++;}
    UART = 0xd;
    while(delayln_i){delayln_i--;}
    return 0;
}

void SerialWrite(char charactere0){
    short delay_j = 0;
    UART = charactere0|0x100;
    while(STATUS&0x02)delay_j++;
    UART &= 0xFF;
    while(delay_j)delay_j--;
    return 0;
}

void SerialRead(char* SerialRead_input_message, int len_input_message){
    char tmp=0;
    int cnt_in=0;
    while(tmp!='\r'){
        while((STATUS&0x4)==0){}
        delay_ms(50);
        tmp = UART;
        SerialWrite(tmp);
        if(tmp==8){ // backspace
            if(cnt_in){
                cnt_in--;
            }
            SerialRead_input_message[cnt_in]=0;
        }else if(cnt_in<len_input_message){
            SerialRead_input_message[cnt_in]=tmp;
            cnt_in++;
        }
    }
    SerialRead_input_message[cnt_in-1]='\0';
    return 0;
}

void digitalWrite(char pin_write, char state){
    if(pin_write<=15){
        pin_write = 1 << pin_write;
        if(state){
            GPO0 |= pin_write;
        }else{
            GPO0 &= ~pin_write;
        }
    }else{
        pin_write = 1 << (pin_write-16);
        if(state){
            GPO1 |=pin_write;
        }else{
            GPO1 &= ~pin_write;
        }
    }
    return 0;
}

int digitalRead(char pin_read){
    int pin_data;
    if(pin_read<=15){
        pin_data = (GPI0 & (1<<pin_read))>>(pin_read);
    }else{
        pin_data = (GPI1 & (1<<pin_read-15))>>pin_read-15;
    }
    return pin_data;
}



#endif