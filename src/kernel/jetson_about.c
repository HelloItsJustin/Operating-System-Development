#include "jetson_about.h"
#include "jetson_animation.h"
#include "jetson_keyboard.h"
#include "jetson_vga_wrapper.h"

void jetson_about_main(void) {
    VGA_clrscr();
    
    VGA_write(0, 0, "ABOUT JETSON OS", JETSON_PRIMARY, JETSON_BG);
    VGA_putc(79, 0, 'X', JETSON_ACCENT, JETSON_BG);
    
    VGA_write(2, 2, "Jetson OS v1.0", JETSON_ACCENT, JETSON_BG);
    VGA_write(2, 3, "Cyberpunk-Inspired Futuristic Desktop", JETSON_TEXT, JETSON_BG);
    
    VGA_write(2, 5, "Features:", JETSON_ACCENT, JETSON_BG);
    VGA_write(4, 6, "* Starburst boot animation", JETSON_TEXT, JETSON_BG);
    VGA_write(4, 7, "* Orbital application ring", JETSON_TEXT, JETSON_BG);
    VGA_write(4, 8, "* Command terminal", JETSON_TEXT, JETSON_BG);
    VGA_write(4, 9, "* File browser with tree view", JETSON_TEXT, JETSON_BG);
    VGA_write(4, 10, "* Real-time system info", JETSON_TEXT, JETSON_BG);
    
    VGA_write(2, 12, "Author: Justin Thomas", JETSON_ACCENT, JETSON_BG);
    VGA_write(2, 13, "Built from scratch in Assembly and C", JETSON_TEXT, JETSON_BG);
    
    VGA_write(0, 24, "Press ESC to return", JETSON_ACCENT, JETSON_BG);
    
    while (1) {
        uint8_t key = jetson_keyboard_read_async();
        if (key == 27) break;
        jetson_sleep_ms(50);
    }
}
