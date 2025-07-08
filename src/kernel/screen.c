#include <stdint.h>
#include <stddef.h>

// VGA memory constants
#define VIDEO_MEMORY ((uint16_t*)0xB8000)
#define MAX_ROWS 25
#define MAX_COLS 80

// VGA colors
enum VGAColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    PINK = 13,
    YELLOW = 14,
    WHITE = 15
};

static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;
static uint8_t current_color = (WHITE | (BLACK << 4));

static inline uint16_t vga_entry(char c, uint8_t color) {
    return ((uint16_t)color << 8) | (uint16_t)c;
}

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void set_color(uint8_t fg, uint8_t bg) {
    current_color = fg | (bg << 4);
}

void move_cursor(uint8_t row, uint8_t col) {
    uint16_t pos = row * MAX_COLS + col;

    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);
    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

void clear_screen() {
    for (size_t i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        VIDEO_MEMORY[i] = vga_entry(' ', current_color);
    }
    cursor_row = 0;
    cursor_col = 0;
    move_cursor(cursor_row, cursor_col);
}

void scroll() {
    for (int row = 1; row < MAX_ROWS; ++row) {
        for (int col = 0; col < MAX_COLS; ++col) {
            VIDEO_MEMORY[(row - 1) * MAX_COLS + col] =
                VIDEO_MEMORY[row * MAX_COLS + col];
        }
    }

    for (int col = 0; col < MAX_COLS; ++col) {
        VIDEO_MEMORY[(MAX_ROWS - 1) * MAX_COLS + col] = vga_entry(' ', current_color);
    }

    if (cursor_row > 0) cursor_row--;
}

void put_char(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } else if (c == '\b') {
        if (cursor_col > 0) cursor_col--;
        VIDEO_MEMORY[cursor_row * MAX_COLS + cursor_col] = vga_entry(' ', current_color);
    } else {
        VIDEO_MEMORY[cursor_row * MAX_COLS + cursor_col] = vga_entry(c, current_color);
        cursor_col++;
        if (cursor_col >= MAX_COLS) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= MAX_ROWS) {
        scroll();
    }

    move_cursor(cursor_row, cursor_col);
}

void print(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}