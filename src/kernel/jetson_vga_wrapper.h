#pragma once
#include <arch/i686/vga_text.h>
#include "jetson_types.h"

// Wrapper functions to provide consistent VGA interface
void jetson_vga_clear(void);
void jetson_vga_putc_at(int x, int y, char c, vga_color_t fg, vga_color_t bg);
void jetson_vga_write_at(int x, int y, const char* str, vga_color_t fg, vga_color_t bg);
void jetson_vga_clear_line(int y, vga_color_t bg);
void jetson_vga_clear_rect(int x1, int y1, int x2, int y2, vga_color_t bg);

// Convenience macros
#define VGA_clrscr() jetson_vga_clear()
#define VGA_putc(x, y, c, fg, bg) jetson_vga_putc_at(x, y, c, fg, bg)
#define VGA_write(x, y, str, fg, bg) jetson_vga_write_at(x, y, str, fg, bg)
