#include "jetson_vga_wrapper.h"
#include <arch/i686/vga_text.h>

// Internal VGA state (assuming standard VGA text mode)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t*)0xB8000)

static int g_last_cleared_y = -1;

void jetson_vga_clear(void) {
    VGA_clrscr();
    g_last_cleared_y = -1;
}

void jetson_vga_putc_at(int x, int y, char c, vga_color_t fg, vga_color_t bg) {
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;
    }
    
    // Write character to VGA memory directly
    uint16_t* vga_mem = VGA_MEMORY;
    int pos = y * VGA_WIDTH + x;
    
    uint16_t color_code = (bg << 4) | fg;
    vga_mem[pos] = ((uint16_t)c) | (color_code << 8);
}

void jetson_vga_write_at(int x, int y, const char* str, vga_color_t fg, vga_color_t bg) {
    if (!str) return;
    
    int curr_x = x;
    int curr_y = y;
    
    while (*str) {
        if (*str == '\n') {
            curr_x = x;
            curr_y++;
            if (curr_y >= VGA_HEIGHT) curr_y = VGA_HEIGHT - 1;
            str++;
            continue;
        }
        
        if (curr_x >= VGA_WIDTH) {
            curr_x = x;
            curr_y++;
            if (curr_y >= VGA_HEIGHT) curr_y = VGA_HEIGHT - 1;
        }
        
        jetson_vga_putc_at(curr_x, curr_y, *str, fg, bg);
        curr_x++;
        str++;
    }
}

void jetson_vga_clear_line(int y, vga_color_t bg) {
    if (y < 0 || y >= VGA_HEIGHT) return;
    
    for (int x = 0; x < VGA_WIDTH; x++) {
        jetson_vga_putc_at(x, y, ' ', 0, bg);
    }
}

void jetson_vga_clear_rect(int x1, int y1, int x2, int y2, vga_color_t bg) {
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 >= VGA_WIDTH) x2 = VGA_WIDTH - 1;
    if (y2 >= VGA_HEIGHT) y2 = VGA_HEIGHT - 1;
    
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            jetson_vga_putc_at(x, y, ' ', 0, bg);
        }
    }
}
