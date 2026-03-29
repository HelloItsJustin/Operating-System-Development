#include "jetson_vga_color.h"
#include <arch/i686/vga_text.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t*)0xB8000)

static int cursor_x = 0;
static int cursor_y = 0;

void clear_screen_colored(uint8_t bg) {
    uint16_t* vga = VGA_MEMORY;
    uint8_t color = (bg << 4) | 0x0F;
    
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (color << 8) | ' ';
    }
    
    cursor_x = 0;
    cursor_y = 0;
}

void print_char_colored(char c, uint8_t fg, uint8_t bg) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) cursor_y = VGA_HEIGHT - 1;
        return;
    }
    
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) cursor_y = VGA_HEIGHT - 1;
    }
    
    uint16_t* vga = VGA_MEMORY;
    int pos = cursor_y * VGA_WIDTH + cursor_x;
    uint8_t color = (bg << 4) | fg;
    vga[pos] = (color << 8) | c;
    
    cursor_x++;
}

void print_colored(const char* text, uint8_t fg, uint8_t bg) {
    if (!text) return;
    
    while (*text) {
        print_char_colored(*text, fg, bg);
        text++;
    }
}

void print_colored_at(int x, int y, const char* text, uint8_t fg, uint8_t bg) {
    cursor_x = x;
    cursor_y = y;
    print_colored(text, fg, bg);
}

void draw_box(int x1, int y1, int x2, int y2, uint8_t fg, uint8_t bg) {
    uint16_t* vga = VGA_MEMORY;
    uint8_t color = (bg << 4) | fg;
    
    // Top and bottom borders
    for (int x = x1; x <= x2; x++) {
        vga[y1 * VGA_WIDTH + x] = (color << 8) | '-';
        vga[y2 * VGA_WIDTH + x] = (color << 8) | '-';
    }
    
    // Left and right borders
    for (int y = y1; y <= y2; y++) {
        vga[y * VGA_WIDTH + x1] = (color << 8) | '|';
        vga[y * VGA_WIDTH + x2] = (color << 8) | '|';
    }
    
    // Corners
    vga[y1 * VGA_WIDTH + x1] = (color << 8) | '+';
    vga[y1 * VGA_WIDTH + x2] = (color << 8) | '+';
    vga[y2 * VGA_WIDTH + x1] = (color << 8) | '+';
    vga[y2 * VGA_WIDTH + x2] = (color << 8) | '+';
}
