#ifndef PIXEL_H
#define PIXEL_H

void clear_screen(char* screen_clear, int size_screen){
    int i=0;
    while(i<size_screen){
        screen_clear[i]='.';
        i++;
    }
    return 0;
}

void print_screen(char* screen, int width_x, int heigth_y){
    int save_width = heigth_y;
    while(width_x){
        width_x--;
        while(heigth_y){
            heigth_y--;
            SerialWrite(screen[(width_x<<5) + heigth_y]);
            SerialWrite(' ');
        }
        heigth_y=save_width;
        SerialWrite('\n');
        SerialWrite('\r');
    }
    return 0;
}
void set_pixel(char* screen_set_pixel, int set_pixel_x, int set_pixel_y){
    screen_set_pixel[(set_pixel_x<<5) + set_pixel_y]='#';
    return 0;
}

#endif