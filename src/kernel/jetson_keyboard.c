#include "jetson_keyboard.h"
#include <arch/i686/io.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_OUTPUT_BUFFER_FULL 0x01

static uint8_t g_last_scancode = 0;
static uint8_t g_key_released = 1;

static const char g_scancode_map[] = {
    0,    27,   '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\n', 0,    'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',  0,    ' ',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    '7',  '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};

void jetson_keyboard_init(void) {
    g_last_scancode = 0;
    g_key_released = 1;
}

uint8_t jetson_keyboard_read_async(void) {
    uint8_t status = i686_inb(KEYBOARD_STATUS_PORT);
    if (!(status & KEYBOARD_OUTPUT_BUFFER_FULL)) {
        return 0;
    }
    
    uint8_t scancode = i686_inb(KEYBOARD_DATA_PORT);
    
    if (scancode & 0x80) {
        g_key_released = 1;
        return 0;
    }
    
    if (scancode == g_last_scancode && !g_key_released) {
        return 0;
    }
    
    g_last_scancode = scancode;
    g_key_released = 0;
    
    if (scancode < sizeof(g_scancode_map)) {
        return g_scancode_map[scancode];
    }
    
    return 0;
}

uint8_t jetson_keyboard_read_blocking(void) {
    uint8_t key = 0;
    while ((key = jetson_keyboard_read_async()) == 0) {
        // Busy wait
    }
    return key;
}

void jetson_keyboard_clear_buffer(void) {
    while (i686_inb(KEYBOARD_STATUS_PORT) & KEYBOARD_OUTPUT_BUFFER_FULL) {
        i686_inb(KEYBOARD_DATA_PORT);
    }
    g_last_scancode = 0;
    g_key_released = 1;
}
