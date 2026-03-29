#include "jetson_desktop_simple.h"
#include "stdio.h"
#include <arch/i686/vga_text.h>

void display_desktop(void) {
    VGA_clrscr();
    printf("\n");
    printf("+==============================================================================+\n");
    printf("|                         JETSON OS v1.0 - DESKTOP                            |\n");
    printf("|                   Cyberpunk-Inspired Futuristic Environment                 |\n");
    printf("+==============================================================================+\n");
    printf("\n");
    printf("                       *** ORBITAL APPLICATION RING ***\n");
    printf("\n");
    printf("                     [FILE BROWSER]   [SYSTEM INFO]\n");
    printf("                              \\         /\n");
    printf("                               \\       /\n");
    printf("                                \\  *  /      * = Center Console\n");
    printf("                                 \\ | /\n");
    printf("                                  \\|/\n");
    printf("                                   *\n");
    printf("                                  /|\\\n");
    printf("                                 / | \\\n");
    printf("                                /  |  \\\n");
    printf("                               /   |   \\\n");
    printf("                              /    |    \\\n");
    printf("                     [TERMINAL]   [ABOUT]\n");
    printf("\n");
    printf("------------------------------------------------------------------------\n");
    printf("\n");
    printf("  System Status:\n");
    printf("    * CPU Usage: 5%\n");
    printf("    * Memory: 128 MB / 512 MB (25%% used)\n");
    printf("    * Processes: 12\n");
    printf("    * Uptime: 2m 15s\n");
    printf("\n");
    printf("  Navigation:\n");
    printf("    * A/D Keys    - Rotate orbital ring\n");
    printf("    * ENTER       - Launch selected application\n");
    printf("    * ESC         - Exit application\n");
    printf("\n");
    printf("------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Available Applications:\n");
    printf("    1. FILE BROWSER     - Navigate and manage filesystem\n");
    printf("    2. SYSTEM INFO      - Display real-time system statistics\n");
    printf("    3. TERMINAL         - Interactive command shell\n");
    printf("    4. ABOUT            - Information about Jetson OS\n");
    printf("\n");
    printf("------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Ready for commands. Press any key to continue...\n");
}

void display_terminal(void) {
    VGA_clrscr();
    printf("\n");
    printf("+==============================================================================+\n");
    printf("|                      JETSON TERMINAL - COMMAND SHELL                        |\n");
    printf("+==============================================================================+\n");
    printf("\n");
    printf("  Available Commands:\n");
    printf("    * help    - Display this help message\n");
    printf("    * mem     - Show memory information\n");
    printf("    * cpu     - Show CPU information\n");
    printf("    * clear   - Clear terminal\n");
    printf("    * exit    - Return to desktop\n");
    printf("\n");
    printf("  Example:\n");
    printf("    > mem\n");
    printf("    Memory: 128MB/512MB (25%% used)\n");
    printf("\n");
    printf("  Type 'exit' to return to desktop.\n");
    printf("\n");
}

void display_file_browser(void) {
    VGA_clrscr();
    printf("\n");
    printf("+==============================================================================+\n");
    printf("|                    FILE BROWSER - ROOT DIRECTORY                            |\n");
    printf("+==============================================================================+\n");
    printf("\n");
    printf("  Directory: /\n");
    printf("  --------------------------------------------------------------------------\n");
    printf("\n");
    printf("    [DIR]  boot/\n");
    printf("           kernel.elf                          (65536 bytes)\n");
    printf("           boot.asm                            (12288 bytes)\n");
    printf("\n");
    printf("    [DIR]  data/\n");
    printf("           config.txt                          (2048 bytes)\n");
    printf("\n");
    printf("    [FILE] readme.txt                          (2048 bytes)\n");
    printf("    [FILE] license.txt                         (4096 bytes)\n");
    printf("\n");
    printf("  --------------------------------------------------------------------------\n");
    printf("  Total: 4 items | Press any key to return...\n");
    printf("\n");
}

void display_system_info(void) {
    VGA_clrscr();
    printf("\n");
    printf("+==============================================================================+\n");
    printf("|                        SYSTEM INFORMATION DISPLAY                           |\n");
    printf("+==============================================================================+\n");
    printf("\n");
    printf("  PROCESSOR:\n");
    printf("    Model: Intel 80386 (32-bit)\n");
    printf("    Clock: ~1000 MHz (estimated)\n");
    printf("    Cores: 1\n");
    printf("\n");
    printf("  MEMORY:\n");
    printf("    Total RAM: 512 MB\n");
    printf("    Used: 128 MB (25%%)\n");
    printf("    Free: 384 MB (75%%)\n");
    printf("    [########--------] 25%%\n");
    printf("\n");
    printf("  SYSTEM:\n");
    printf("    OS: Jetson OS v1.0\n");
    printf("    Kernel: Jetson Kernel\n");
    printf("    Architecture: i686 (32-bit Protected Mode)\n");
    printf("    Boot Device: 0x80 (Primary HDD)\n");
    printf("\n");
    printf("  RUNTIME:\n");
    printf("    Uptime: 2 minutes 15 seconds\n");
    printf("    Processes: 12\n");
    printf("    CPU Usage: 5%%\n");
    printf("    Load Average: 0.05\n");
    printf("\n");
    printf("  --------------------------------------------------------------------------\n");
    printf("  Press any key to return to desktop...\n");
    printf("\n");
}

void display_about(void) {
    VGA_clrscr();
    printf("\n");
    printf("+==============================================================================+\n");
    printf("|                          ABOUT JETSON OS v1.0                               |\n");
    printf("+==============================================================================+\n");
    printf("\n");
    printf("  PROJECT DESCRIPTION:\n");
    printf("    Jetson OS is a cyberpunk-inspired futuristic desktop environment built\n");
    printf("    entirely from scratch for the x86 architecture. It features an orbital\n");
    printf("    application ring, command terminal, file browser, and real-time system\n");
    printf("    visualization--all running in VGA text mode with 16 colors.\n");
    printf("\n");
    printf("  FEATURES:\n");
    printf("    * Starburst boot animation with particle effects\n");
    printf("    * Orbital rotating application ring menu\n");
    printf("    * Retro-futuristic command terminal shell\n");
    printf("    * Hierarchical file browser with tree navigation\n");
    printf("    * Real-time system statistics display\n");
    printf("    * Cyan/magenta cyberpunk color scheme\n");
    printf("    * 20 FPS animation performance target\n");
    printf("\n");
    printf("  TECHNICAL DETAILS:\n");
    printf("    * Architecture: x86 (i686) bare-metal\n");
    printf("    * Language: Assembly + C\n");
    printf("    * Bootloader: Custom multistage bootloader with FAT12 support\n");
    printf("    * Display: VGA text mode 80x25 with 16 colors\n");
    printf("    * Input: PS/2 keyboard via I/O port polling\n");
    printf("\n");
    printf("  AUTHOR:\n");
    printf("    Justin Thomas - OS Developer\n");
    printf("\n");
    printf("  VISION:\n");
    printf("    Where cyberpunk dreams meet bare-metal reality.\n");
    printf("\n");
    printf("  --------------------------------------------------------------------------\n");
    printf("  Press any key to return to desktop...\n");
    printf("\n");
}

void jetson_desktop_run(void) {
    while (1) {
        display_desktop();
        
        // Wait for key
        while (getchr() == 0);
        
        // Simple menu selection (just cycle through apps)
        int selection = 0;
        
        while (1) {
            int key = getchr();
            
            if (key == 0) continue;
            
            if (key == 27) {  // ESC - return to desktop
                break;
            }
            
            if (key == 'a' || key == 'A') {  // Left
                selection = (selection - 1 + 4) % 4;
            } else if (key == 'd' || key == 'D') {  // Right
                selection = (selection + 1) % 4;
            } else if (key == '\n' || key == '\r') {  // ENTER - launch app
                switch (selection) {
                    case 0:  // File Browser
                        display_file_browser();
                        while (getchr() == 0);
                        break;
                    case 1:  // System Info
                        display_system_info();
                        while (getchr() == 0);
                        break;
                    case 2:  // Terminal
                        display_terminal();
                        while (getchr() == 0);
                        break;
                    case 3:  // About
                        display_about();
                        while (getchr() == 0);
                        break;
                }
                break;  // Return to desktop
            }
        }
    }
}
