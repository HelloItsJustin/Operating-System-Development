#include "jetson_desktop_interactive.h"
#include "jetson_vga_color.h"
#include <arch/i686/vga_text.h>
#include "stdio.h"

#define CYAN VGA_LIGHTCYAN
#define MAGENTA VGA_LIGHTMAGENTA
#define GREEN VGA_LIGHTGREEN
#define RED VGA_LIGHTRED
#define WHITE VGA_WHITE
#define BLACK VGA_BLACK
#define YELLOW VGA_YELLOW

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 100000; i++);
}

void jetson_boot_animation(void) {
    clear_screen_colored(BLACK);
    
    print_colored_at(25, 3, "JETSON OS v1.0", CYAN, BLACK);
    delay_ms(500);
    
    print_colored_at(15, 5, "STARBURST BOOT ANIMATION", MAGENTA, BLACK);
    delay_ms(500);
    
    print_colored_at(10, 8, "Initializing systems...", CYAN, BLACK);
    
    // Animated progress bar
    for (int i = 0; i < 50; i++) {
        printf("[");
        for (int j = 0; j < i; j++) printf("=");
        for (int j = i; j < 50; j++) printf(" ");
        printf("] %d%%\n", (i * 100) / 50);
        delay_ms(100);
    }
    
    print_colored_at(10, 12, "MEMORY DETECTED: 512 MB", GREEN, BLACK);
    delay_ms(500);
    
    print_colored_at(10, 14, "Loading Orbital Desktop...", CYAN, BLACK);
    delay_ms(1000);
    
    print_colored_at(10, 16, "READY FOR COMMANDS", GREEN, BLACK);
    delay_ms(1000);
}

void draw_orbital_ring(int selected) {
    clear_screen_colored(BLACK);
    
    // Title
    print_colored_at(20, 0, "JETSON OS v1.0 - ORBITAL DESKTOP", CYAN, BLACK);
    print_colored_at(18, 1, "Cyberpunk-Inspired Futuristic Environment", MAGENTA, BLACK);
    
    // Draw box
    draw_box(5, 3, 75, 21, CYAN, BLACK);
    
    // Orbital visualization
    print_colored_at(35, 5, "***  ORBITAL RING  ***", MAGENTA, BLACK);
    
    // App positions and names
    const char* apps[] = {"FILE BROWSER", "SYSTEM INFO", "TERMINAL", "ABOUT"};
    const int colors[] = {CYAN, MAGENTA, GREEN, YELLOW};
    
    // Center
    print_colored_at(38, 10, "*", CYAN, BLACK);
    
    // Top (index 0)
    uint8_t top_color = (selected == 0) ? YELLOW : colors[0];
    print_colored_at(30, 6, "[", top_color, BLACK);
    print_colored(apps[0], top_color, BLACK);
    print_colored("]", top_color, BLACK);
    
    // Right (index 1)
    uint8_t right_color = (selected == 1) ? YELLOW : colors[1];
    print_colored_at(60, 10, "[", right_color, BLACK);
    print_colored(apps[1], right_color, BLACK);
    print_colored("]", right_color, BLACK);
    
    // Bottom (index 3)
    uint8_t bottom_color = (selected == 3) ? YELLOW : colors[3];
    print_colored_at(50, 14, "[", bottom_color, BLACK);
    print_colored(apps[3], bottom_color, BLACK);
    print_colored("]", bottom_color, BLACK);
    
    // Left (index 2)
    uint8_t left_color = (selected == 2) ? YELLOW : colors[2];
    print_colored_at(10, 10, "[", left_color, BLACK);
    print_colored(apps[2], left_color, BLACK);
    print_colored("]", left_color, BLACK);
    
    // Status bar
    print_colored_at(7, 19, "CPU: 5% | MEM: 128MB/512MB | Ready", CYAN, BLACK);
    print_colored_at(7, 20, "Navigate: A/D | Select: ENTER | Help: H", MAGENTA, BLACK);
}

void show_app_screen(int app_id) {
    clear_screen_colored(BLACK);
    
    print_colored_at(20, 0, "JETSON OS v1.0 - APPLICATION", CYAN, BLACK);
    draw_box(5, 2, 75, 22, CYAN, BLACK);
    
    switch(app_id) {
        case 0:
            print_colored_at(25, 3, "FILE BROWSER", MAGENTA, BLACK);
            print_colored_at(7, 5, "Directory: /", CYAN, BLACK);
            print_colored_at(7, 7, "[DIR]  boot/", GREEN, BLACK);
            print_colored_at(10, 8, "kernel.elf (65536 B)", WHITE, BLACK);
            print_colored_at(10, 9, "boot.asm (12288 B)", WHITE, BLACK);
            print_colored_at(7, 11, "[DIR]  data/", GREEN, BLACK);
            print_colored_at(10, 12, "config.txt (2048 B)", WHITE, BLACK);
            print_colored_at(7, 14, "[FILE] readme.txt (2048 B)", YELLOW, BLACK);
            break;
            
        case 1:
            print_colored_at(25, 3, "SYSTEM INFORMATION", MAGENTA, BLACK);
            print_colored_at(7, 5, "PROCESSOR:", CYAN, BLACK);
            print_colored_at(9, 6, "Model: Intel 80386 (32-bit)", WHITE, BLACK);
            print_colored_at(9, 7, "Clock: ~1000 MHz", WHITE, BLACK);
            print_colored_at(7, 9, "MEMORY:", CYAN, BLACK);
            print_colored_at(9, 10, "Total: 512 MB", WHITE, BLACK);
            print_colored_at(9, 11, "Used: 128 MB (25%)", GREEN, BLACK);
            print_colored_at(9, 12, "Free: 384 MB (75%)", GREEN, BLACK);
            print_colored_at(9, 13, "[########--------] 25%", YELLOW, BLACK);
            print_colored_at(7, 15, "OS: Jetson OS v1.0", CYAN, BLACK);
            print_colored_at(7, 16, "Architecture: i686 Protected Mode", WHITE, BLACK);
            break;
            
        case 2:
            print_colored_at(28, 3, "COMMAND TERMINAL", MAGENTA, BLACK);
            print_colored_at(7, 5, "Available Commands:", CYAN, BLACK);
            print_colored_at(9, 6, "help - Show help", WHITE, BLACK);
            print_colored_at(9, 7, "mem  - Memory info", WHITE, BLACK);
            print_colored_at(9, 8, "cpu  - CPU info", WHITE, BLACK);
            print_colored_at(9, 9, "exit - Return", WHITE, BLACK);
            print_colored_at(7, 12, "> ", MAGENTA, BLACK);
            print_colored("mem", GREEN, BLACK);
            print_colored_at(7, 13, "Memory: 128MB/512MB (25% used)", WHITE, BLACK);
            print_colored_at(7, 15, "> ", MAGENTA, BLACK);
            break;
            
        case 3:
            print_colored_at(28, 3, "ABOUT JETSON OS", MAGENTA, BLACK);
            print_colored_at(7, 5, "Jetson OS v1.0 - Cyberpunk Desktop", CYAN, BLACK);
            print_colored_at(7, 7, "Features:", YELLOW, BLACK);
            print_colored_at(9, 8, "* Starburst boot animation", GREEN, BLACK);
            print_colored_at(9, 9, "* Orbital application ring", GREEN, BLACK);
            print_colored_at(9, 10, "* Command terminal", GREEN, BLACK);
            print_colored_at(9, 11, "* File browser", GREEN, BLACK);
            print_colored_at(7, 13, "Author: Justin Thomas", CYAN, BLACK);
            print_colored_at(7, 14, "Vision: Where cyberpunk dreams meet bare-metal", MAGENTA, BLACK);
            break;
    }
    
    print_colored_at(7, 23, "Press ESC to return to desktop", CYAN, BLACK);
}

void jetson_desktop_interactive(void) {
    int selected = 0;
    
    while (1) {
        draw_orbital_ring(selected);
        
        // Wait for input
        int key = 0;
        while (key == 0) {
            key = getchr();
            delay_ms(10);
        }
        
        if (key == 27) {
            break;
        } else if (key == 'a' || key == 'A') {
            selected = (selected - 1 + 4) % 4;
        } else if (key == 'd' || key == 'D') {
            selected = (selected + 1) % 4;
        } else if (key == '\n' || key == '\r') {
            show_app_screen(selected);
            
            // Wait for ESC in app
            while (1) {
                key = getchr();
                if (key == 27) break;
                delay_ms(10);
            }
        }
    }
}
