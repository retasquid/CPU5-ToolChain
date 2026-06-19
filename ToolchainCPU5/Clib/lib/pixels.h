#ifndef PIXEL_H
#define PIXEL_H
#include "lcd_font.h"



void clear_screen(short clear_screen_motif){
    int* ptr_clear_screen = 0x8000;
    while(ptr_clear_screen<0xBE80){
        *ptr_clear_screen = clear_screen_motif;
        ptr_clear_screen++;
        *ptr_clear_screen = clear_screen_motif;
        ptr_clear_screen++;
        *ptr_clear_screen = clear_screen_motif;
        ptr_clear_screen++;
        *ptr_clear_screen = clear_screen_motif;
        ptr_clear_screen++;
    }
    return;
}

void set_pixel(int x_set_pixel, int y_set_pixel){
    int* ptr_set_pixel = 0x8000 + (x_set_pixel>>4) + (y_set_pixel<<5) + (y_set_pixel<<3);
    *ptr_set_pixel = (1<<(15-(x_set_pixel&0xf)))|(*ptr_set_pixel);    // 0xffff
    return ;
}

void clear_pixel(int x_clear_pixel, int y_clear_pixel){
    int* ptr_clear_pixel = 0x8000 + (x_clear_pixel>>4) + (y_clear_pixel<<5) + (y_clear_pixel<<3);
    *ptr_clear_pixel = (~(1<<(15-(x_clear_pixel&0xf))))&(*ptr_clear_pixel);    // 0xffff
    return ;
}

void draw_lineH(short x_draw_lineH, short y_draw_lineH, short x2_draw_lineH, short y2_draw_lineH) {
    short dx_draw_lineH;
    if (x_draw_lineH > x2_draw_lineH) {
        dx_draw_lineH = x_draw_lineH;
        x_draw_lineH = x2_draw_lineH;   
        x2_draw_lineH = dx_draw_lineH;
        dx_draw_lineH = y_draw_lineH;
        y_draw_lineH = y2_draw_lineH;
        y2_draw_lineH = dx_draw_lineH;
    }
    dx_draw_lineH = x2_draw_lineH - x_draw_lineH;
    short dy_draw_lineH = y2_draw_lineH - y_draw_lineH;
    short dir_draw_lineH;

    if (y2_draw_lineH > y_draw_lineH) {
        dir_draw_lineH = 1;
    }else{
        dir_draw_lineH = -1;
        dy_draw_lineH = -dy_draw_lineH;
    }
    
    if(dx_draw_lineH) {
        short y0_draw_lineH = y_draw_lineH;
        short p_draw_lineH = (dy_draw_lineH << 1) - dx_draw_lineH;
        short i_draw_lineH = 0;
        while(i_draw_lineH <= dx_draw_lineH) {
            set_pixel(x_draw_lineH + i_draw_lineH, y0_draw_lineH);
            if (p_draw_lineH >= 0) {
                y0_draw_lineH +=dir_draw_lineH;
                p_draw_lineH -= (dx_draw_lineH << 1);
            }
            p_draw_lineH += (dy_draw_lineH << 1);
            i_draw_lineH++;
        }
    }
    return;
}

void draw_lineV(short x_draw_lineV, short y_draw_lineV, short x2_draw_lineV, short y2_draw_lineV) {
    short dx_draw_lineV;
    if (y_draw_lineV > y2_draw_lineV) {
        dx_draw_lineV = y_draw_lineV;
        y_draw_lineV = y2_draw_lineV;   
        y2_draw_lineV = dx_draw_lineV;
        dx_draw_lineV = x_draw_lineV;
        x_draw_lineV = x2_draw_lineV;
        x2_draw_lineV = dx_draw_lineV;
    }

    dx_draw_lineV = x2_draw_lineV - x_draw_lineV;
    short dy_draw_lineV = y2_draw_lineV - y_draw_lineV;
    short dir_draw_lineV;

    if (x2_draw_lineV > x_draw_lineV) {
        dir_draw_lineV = 1;
    } else {
        dir_draw_lineV = -1;
        dx_draw_lineV = -dx_draw_lineV;
    }

    if (dy_draw_lineV) {
        short p_draw_lineV = (dy_draw_lineV << 1) - dx_draw_lineV;
        short x0_draw_lineV = x_draw_lineV;
        short i_draw_lineV = 0;
        while(i_draw_lineV <= dy_draw_lineV){
            set_pixel(x0_draw_lineV, y_draw_lineV + i_draw_lineV);

            if (p_draw_lineV >= 0) {
                x0_draw_lineV += dir_draw_lineV;
                p_draw_lineV -= (dy_draw_lineV << 1);
            }
            p_draw_lineV += (dx_draw_lineV << 1);
            i_draw_lineV++;
        }
    }
    return;
}

void draw_line(short x0_draw_line, short y0_draw_line, short x1_draw_line, short y1_draw_line) {
    short dx_draw_line;
    if (x0_draw_line>x1_draw_line) {
        dx_draw_line = x0_draw_line - x1_draw_line;
    }else{
        dx_draw_line = x1_draw_line - x0_draw_line;
    }
    short dy_draw_line;
     if (y0_draw_line>y1_draw_line) {
        dy_draw_line = y0_draw_line - y1_draw_line;
    }else{
        dy_draw_line = y1_draw_line - y0_draw_line;
    }

    if (dx_draw_line > dy_draw_line) {
        draw_lineH(x0_draw_line, y0_draw_line, x1_draw_line, y1_draw_line);
    } else {
        draw_lineV(x0_draw_line, y0_draw_line, x1_draw_line, y1_draw_line);
    }
    return;
}

void draw_rectangle(short x0_rect, short y0_rect, short x1_rect, short y1_rect){
    short i_rect = x0_rect;
    while(i_rect <= x1_rect){
        set_pixel(i_rect, y0_rect);
        set_pixel(i_rect, y1_rect);
        i_rect++;
    }
    i_rect = y0_rect;
    while(i_rect < y1_rect){
        set_pixel(x0_rect, i_rect);
        set_pixel(x1_rect, i_rect);
        i_rect++;
    }
    return;
}

void draw_char(short x_char, short y_char, char c) {
    if (c < 32)  return; 
    if (c > 126) return; 

    c-=32;
    short* bitmap = &font;
    bitmap +=(c<<4) + (c<<2) + c;
    char debug_a[5];
    for(short row = -1; row < HEIGHT; row++) {
        short ptr_line = bitmap+row;
        short line = *ptr_line;

        for (short col = -1; col < LENGHT; col++) {
            if (line & (1 << (LENGHT - 1 - col))){
                set_pixel(x_char + col ,y_char + row);
            }else{
                clear_pixel(x_char + col ,y_char + row);
            }
        }
    }
    return;
}

void draw_text(short x_text, short y_text, char* text) {
    while (*text) {
        draw_char(x_text, y_text, *text);
        x_text += 11;
        text++;
    }
    return;
}

#endif