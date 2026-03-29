#include "jetson_file_browser.h"
#include "jetson_types.h"
#include "jetson_animation.h"
#include "jetson_keyboard.h"
#include "jetson_utils.h"
#include "jetson_vga_wrapper.h"

#define MAX_ENTRIES 32

typedef struct {
    char name[64];
    int is_dir;
    int expanded;
    int depth;
    int size;
} file_entry_t;

static file_entry_t g_entries[MAX_ENTRIES];
static int g_entry_count = 0;
static int g_selected = 0;

void jetson_file_browser_main(void) {
    jetson_file_browser_init();
    
    while (1) {
        jetson_file_browser_update();
        jetson_file_browser_render();
        
        uint8_t key = jetson_keyboard_read_async();
        if (key == 27) break;  // ESC to exit
        if (key != 0) {
            jetson_file_browser_input(key);
        }
        
        jetson_sleep_ms(50);
    }
}

void jetson_file_browser_init(void) {
    VGA_clrscr();
    
    g_entry_count = 4;
    strcpy_safe(g_entries[0].name, "boot", 64);
    g_entries[0].is_dir = 1;
    g_entries[0].expanded = 1;
    g_entries[0].depth = 0;
    
    strcpy_safe(g_entries[1].name, "kernel.elf", 64);
    g_entries[1].is_dir = 0;
    g_entries[1].depth = 1;
    g_entries[1].size = 65536;
    
    strcpy_safe(g_entries[2].name, "data", 64);
    g_entries[2].is_dir = 1;
    g_entries[2].expanded = 0;
    g_entries[2].depth = 0;
    
    strcpy_safe(g_entries[3].name, "readme.txt", 64);
    g_entries[3].is_dir = 0;
    g_entries[3].depth = 0;
    g_entries[3].size = 2048;
    
    g_selected = 0;
}

void jetson_file_browser_render(void) {
    VGA_clrscr();
    
    VGA_write(0, 0, "FILE BROWSER - Root", JETSON_PRIMARY, JETSON_BG);
    VGA_write(70, 0, "Items: ", JETSON_ACCENT, JETSON_BG);
    
    for (int i = 0; i < g_entry_count && i < 22; i++) {
        file_entry_t* e = &g_entries[i];
        
        int x = 2 + (e->depth * 2);
        vga_color_t color = (i == g_selected) ? JETSON_ACCENT : JETSON_PRIMARY;
        
        if (i == g_selected) {
            VGA_putc(0, i + 1, '>', color, JETSON_BG);
        }
        
        if (e->is_dir) {
            VGA_putc(x, i + 1, e->expanded ? 'v' : '>', color, JETSON_BG);
            VGA_write(x + 2, i + 1, e->name, color, JETSON_BG);
        } else {
            VGA_putc(x, i + 1, '-', color, JETSON_BG);
            VGA_write(x + 2, i + 1, e->name, color, JETSON_BG);
        }
    }
    
    VGA_write(0, 24, "W/S=Nav | ENTER=Select | ESC=Menu", JETSON_ACCENT, JETSON_BG);
}

void jetson_file_browser_input(char key) {
    switch (key) {
        case 'w':
            if (g_selected > 0) g_selected--;
            break;
        case 's':
            if (g_selected < g_entry_count - 1) g_selected++;
            break;
        case '\n':
            if (g_entries[g_selected].is_dir) {
                g_entries[g_selected].expanded = !g_entries[g_selected].expanded;
            }
            break;
    }
}

void jetson_file_browser_update(void) {
    // Animation updates
}
