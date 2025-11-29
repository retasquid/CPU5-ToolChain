#ifndef SHELL_H
#define SHELL_H


void help_cmd(){
    char h[19] = "\n\rCommande -help\n\r";
    h[18] = '\0';
    SerialPrint(&h);
    return 0;
}
void exit_cmd(){
    char e[19] = "\n\rCommande -exit\n\r";
    e[18] = '\0';
    SerialPrint(&e);
    return 0;
}

char command_decode(char* cmd_shell) {
    char tmp_command_decode[5]="help";
    tmp_command_decode[4] = '\0';
    if(strcmp(&tmp_command_decode, cmd_shell) == 0) {
        help_cmd();
        return 1;
    }
    char tmp_command_decode1[5]="exit";
    tmp_command_decode[4] = '\0';
    if(strcmp(&tmp_command_decode1, cmd_shell) == 0) {
        exit_cmd();
        return 2;
    }
    char i12[24] = "\n\rCommande inconnue :\n\r";
    i12[23] = '\0';
    SerialPrint(&i12);
    SerialPrint(cmd_shell);
    return 0; // Commande inconnue
}

#endif