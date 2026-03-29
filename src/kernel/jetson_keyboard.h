#pragma once
#include <stdint.h>

void jetson_keyboard_init(void);
uint8_t jetson_keyboard_read_async(void);
uint8_t jetson_keyboard_read_blocking(void);
void jetson_keyboard_clear_buffer(void);
