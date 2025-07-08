#pragma once

#include <stdint.h>

void set_color(uint8_t fg, uint8_t bg);
void clear_screen();
void put_char(char c);
void print(const char* str);
void printf(const char* fmt, ...);