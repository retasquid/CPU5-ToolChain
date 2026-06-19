#ifndef SHELL_H
#define SHELL_H
#include "Arduino.h"
#include "String.h"
#include "stdlib.h"
#include "FileSystem.h"
#include "pixels.h"

void help_cmd(){
    SerialPrintln("Commandes disponibles :");
    SerialPrintln("ls");
    SerialPrintln("cd <path>");
    SerialPrintln("nano <file>");
    SerialPrintln("clear");
    SerialPrintln("touch <file>");
    SerialPrintln("plot <x> <y>");
    return;
}
void ls_cmd(){
    SerialPrintln("Commande -ls");
    int cnt_ls = 0;
    char file_listing[32];
    char ptr_file_listing;
    while(cnt_ls<16){
        ptr_file_listing = file_name[cnt_ls];
        SerialPrintln(ptr_file_listing);
        cnt_ls++;
    }
    return;
}
void cd_cmd(char* path_cd){
    SerialPrint("Commande -cd ");
    SerialPrintln(path_cd);
    return;
}
void nano_cmd(char* file_nano){
    SerialPrint("Commande -nano ");
    SerialPrintln(file_nano);
    draw_text(320, 200, file_nano);
    return;
}
void clear_cmd(){
    char clear_seq[8] = {27, 91, 72, 27, 91, 50, 74, 0}; // ESC [ H ESC [ 2 J
    SerialPrint(&clear_seq);
    
    clear_screen(0x0);
    return 0;
}
void touch_cmd(char* file_touch){
    createFileName(file_touch);
    SerialPrint("Created :  ");
    SerialPrintln(file_touch);
    return;
}
void plot_cmd(char* x_plot_cmd, char* y_plot_cmd){
    int x_plot = atoi(x_plot_cmd);
    int y_plot = atoi(y_plot_cmd);
    SerialPrint("Ploted at : X=");
    SerialPrint(x_plot_cmd);
    SerialPrint(", Y=");
    SerialPrintln(y_plot_cmd);
    draw_line(320, 200, x_plot, y_plot);
    return;
}

/* return the number of arguments */
int argParser(char* cmd_shell_toParse, char* arg1, char* arg2){
    int i = 0;
    int j = 0;
    // Skip command
    while(cmd_shell_toParse[i] != ' ') {
        if(cmd_shell_toParse[i] == '\0') return 0;
            i++;
    }
    // Skip spaces
    while(cmd_shell_toParse[i] == ' '){
        i++;
    }
    if(cmd_shell_toParse[i] == '\0') return 0;
    // Parse arg1
    while(cmd_shell_toParse[i] != ' ') {
        if(cmd_shell_toParse[i] == '\0'){
            arg1[j] = '\0';
            return 1;
        }
        arg1[j] = cmd_shell_toParse[i];
        i++;
        j++;
    }
    arg1[j] = '\0';
    j = 0;
    // Skip spaces
    while(cmd_shell_toParse[i] == ' '){
        i++;
    }
    if(cmd_shell_toParse[i] == '\0') return 1;
    // Parse arg2
    while(cmd_shell_toParse[i] != ' ') {
        if(cmd_shell_toParse[i] == '\0'){
            arg2[j] = '\0';
            return 2;
        } 
        arg2[j] = cmd_shell_toParse[i];
        i++;
        j++;
    }
    // Skip spaces
    while(cmd_shell_toParse[i] == ' '){
        i++;
    }
    if(cmd_shell_toParse[i] == '\0') return 2;
    return 3;
}

void argErrorMessage(short arg_num_ErrorMessage){
    SerialPrint("Wrong number of arguments : ");
    char arg_num_ErrorMessage_str[4];
    itoa(arg_num_ErrorMessage, &arg_num_ErrorMessage_str);
    SerialPrintln(&arg_num_ErrorMessage_str);
    return 0;
}

char arg1_cmd[64];
char arg2_cmd[64];
short arg_num;
char command_decode(char* cmd_shell) {
    if(strcmp("help", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 0){
            help_cmd();
        }else{
            argErrorMessage(arg_num);
        }
        return 1;
    }
    if(strcmp("ls", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 0){
            ls_cmd();
        }else{
            argErrorMessage(arg_num);
        }
        return 2;
    }
    if(strcmp("cd", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 1){
            cd_cmd(&arg1_cmd);
        }else{
            argErrorMessage(arg_num);
        }
        return 3;
    }
    if(strcmp("nano", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 1){
            nano_cmd(&arg1_cmd);
        }else{
            argErrorMessage(arg_num);
        }
        return 4;
    }
    if(strcmp("clear", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 0){
            clear_cmd();
        }else{
            argErrorMessage(arg_num);
        }
        return 5;
    }
    if(strcmp("touch", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 1){
            touch_cmd(&arg1_cmd);
        }else{
            argErrorMessage(arg_num);
        }
        return 6;
    }
    if(strcmp("plot", cmd_shell) == 0) {
        arg_num = argParser(cmd_shell, &arg1_cmd, &arg2_cmd);
        if(arg_num == 2){
            plot_cmd(&arg1_cmd, &arg2_cmd);
        }else{
            argErrorMessage(arg_num);
        }
        return 7;
    }
    SerialPrint("Commande inconnue :");
    SerialPrintln(cmd_shell);
    return 0;
}

#endif