#pragma once
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#include <stdint.h>  // ✅ ADD THIS LINE
void VGA_putc(char c);
void VGA_clrscr(void);
void VGA_setcursor(int x, int y);
void VGA_putc_at(int x, int y, char c);
void VGA_puts(const char* str);
void VGA_putcolor(int x, int y, uint8_t color);