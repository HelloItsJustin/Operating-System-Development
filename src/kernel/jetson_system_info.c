#include "jetson_system_info.h"
#include "jetson_animation.h"
#include "jetson_keyboard.h"
#include "jetson_vga_wrapper.h"

void jetson_system_info_main(void) {
    jetson_system_info_init();
    
    while (1) {
        jetson_system_info_update();
        jetson_system_info_render();
        
        uint8_t key = jetson_keyboard_read_async();
        if (key == 27) break;
        
        jetson_sleep_ms(50);
    }
}

void jetson_system_info_init(void) {
    VGA_clrscr();
}

void jetson_system_info_render(void) {
    VGA_clrscr();
    
    VGA_write(0, 0, "SYSTEM INFORMATION", JETSON_PRIMARY, JETSON_BG);
    VGA_putc(79, 0, 'X', JETSON_ACCENT, JETSON_BG);
    
    VGA_write(2, 2, "CPU: i686 (32-bit)", JETSON_ACCENT, JETSON_BG);
    VGA_write(2, 3, "RAM: 512 MB total", JETSON_TEXT, JETSON_BG);
    VGA_write(2, 4, "Used: 128 MB (25%)", JETSON_TEXT, JETSON_BG);
    
    VGA_write(2, 6, "Memory: [", JETSON_TEXT, JETSON_BG);
    for (int i = 0; i < 25; i++) {
        char c = i < 6 ? '#' : '.';
        VGA_putc(11 + i, 6, c, JETSON_SUCCESS, JETSON_BG);
    }
    VGA_write(37, 6, "] 25%", JETSON_TEXT, JETSON_BG);
    
    VGA_write(2, 8, "OS: Jetson OS v1.0", JETSON_ACCENT, JETSON_BG);
    VGA_write(2, 9, "Uptime: 2m 15s", JETSON_TEXT, JETSON_BG);
    VGA_write(2, 10, "Processes: 12", JETSON_TEXT, JETSON_BG);
    
    VGA_write(0, 24, "ESC=Return", JETSON_ACCENT, JETSON_BG);
}

void jetson_system_info_update(void) {
    // Real-time updates
}
