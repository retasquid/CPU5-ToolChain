#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "String.h"

#define MAX_FILE_NAME_LENGTH 32
#define MAX_FILES 16

int file0[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file1[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file2[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file3[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file4[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file5[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file6[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file7[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file8[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file9[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file10[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file11[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file12[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file13[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file14[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file15[MAX_FILE_NAME_LENGTH] = "file0.txt";
int file_name[MAX_FILES];
int file_count = 0;

void initFileSystem(){
    file_name[0] = &file0;
    file_name[1] = &file1;
    file_name[2] = &file2;
    file_name[3] = &file3;
    file_name[4] = &file4;
    file_name[5] = &file5;
    file_name[6] = &file6;
    file_name[7] = &file7;
    file_name[8] = &file8;
    file_name[9] = &file9;
    file_name[10] = &file10;
    file_name[11] = &file11;
    file_name[12] = &file12;
    file_name[13] = &file13;
    file_name[14] = &file14;
    file_name[15] = &file15;
    return 0;
}

char readFileName(int readFileName_index){
    return file_name[readFileName_index];
}

int readFileId(char* readFileId_buffer){
    int readFileID_i = MAX_FILES;
    while(readFileID_i){
        readFileID_i--;
        if(strcmp(file_name[readFileID_i],readFileId_buffer))return readFileID_i;
    }
    return -1;
}

void writeFileName(int writeFileName_index, char* writeFileName_buffer){
    strcpy(file_name[writeFileName_index], writeFileName_buffer);
    return 0;
}

void createFileName(char* createFileName_buffer){
    if(file_count>=MAX_FILES){
        SerialPrintln("Error : Max file number reached");
        return -1;
    }
    strcpy(file_name[file_count], createFileName_buffer);
    file_count++;
    return 0;
}
#endif