#pragma once
#include <stdint.h>

// VGA Color Codes
#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_MAGENTA 5
#define VGA_BROWN 6
#define VGA_LIGHTGRAY 7
#define VGA_DARKGRAY 8
#define VGA_LIGHTBLUE 9
#define VGA_LIGHTGREEN 10
#define VGA_LIGHTCYAN 11
#define VGA_LIGHTRED 12
#define VGA_LIGHTMAGENTA 13
#define VGA_YELLOW 14
#define VGA_WHITE 15

// Print colored text
void print_colored(const char* text, uint8_t fg, uint8_t bg);
void print_colored_at(int x, int y, const char* text, uint8_t fg, uint8_t bg);
void print_char_colored(char c, uint8_t fg, uint8_t bg);
void clear_screen_colored(uint8_t bg);
void draw_box(int x1, int y1, int x2, int y2, uint8_t fg, uint8_t bg);
