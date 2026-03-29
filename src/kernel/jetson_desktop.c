#include "jetson_desktop.h"
#include "jetson_animation.h"
#include "jetson_keyboard.h"
#include "jetson_utils.h"
#include "jetson_vga_wrapper.h"

static orbital_app_t g_apps[MAX_APPS] = {
    {"FILE BROWSER", 0, 8, 0, JETSON_PRIMARY},
    {"SYSTEM INFO", 90, 8, 1, JETSON_ACCENT},
    {"COMMAND SHELL", 180, 8, 2, JETSON_PRIMARY},
    {"ABOUT JETSON", 270, 8, 3, JETSON_ACCENT},
};

static int g_selected_app = 0;
static uint32_t g_last_frame = 0;
static float g_ring_rotation = 0.0f;

static void jetson_app_launch(int app_id);

void jetson_desktop_init(void) {
    VGA_clrscr();
    g_selected_app = 0;
    g_last_frame = jetson_get_ticks();
}

void jetson_desktop_update(void) {
    uint32_t now = jetson_get_ticks();
    uint32_t delta = now - g_last_frame;
    g_last_frame = now;
    
    if (delta < FRAME_TIME_MS) {
        jetson_sleep_ms(FRAME_TIME_MS - delta);
    }
}

void jetson_desktop_render(void) {
    // Only clear the center area, not the entire screen
    jetson_vga_clear_rect(10, 6, 70, 18, JETSON_BG);
    
    int cx = 40, cy = 12;
    
    VGA_putc(cx, cy, '*', JETSON_PRIMARY, JETSON_BG);
    
    // Inner ring (memory)
    for (int i = 0; i < 8; i++) {
        float angle = (i * 3.14159f * 2.0f) / 8.0f;
        int x = cx + (int)(4.0f * cosf(angle));
        int y = cy + (int)(2.0f * sinf(angle));
        VGA_putc(x, y, '.', JETSON_PRIMARY, JETSON_BG);
    }
    
    // Middle ring (CPU)
    for (int i = 0; i < 12; i++) {
        float angle = (i * 3.14159f * 2.0f) / 12.0f;
        int x = cx + (int)(8.0f * cosf(angle));
        int y = cy + (int)(4.0f * sinf(angle));
        VGA_putc(x, y, '.', JETSON_ACCENT, JETSON_BG);
    }
    
    // Application ring
    for (int i = 0; i < MAX_APPS; i++) {
        float angle = ((g_apps[i].angle + g_ring_rotation) * 3.14159f) / 180.0f;
        int x = cx + (int)(12.0f * cosf(angle));
        int y = cy + (int)(6.0f * sinf(angle));
        
        vga_color_t color = (i == g_selected_app) ? JETSON_ACCENT : g_apps[i].color;
        VGA_putc(x, y, '+', color, JETSON_BG);
    }
    
    VGA_write(0, 24, "JETSON OS v1.0 | CPU: 5% | MEM: 128MB | Ready", JETSON_PRIMARY, JETSON_BG);
}

void jetson_desktop_input(char key) {
    switch (key) {
        case 'a':
            g_ring_rotation -= 15.0f;
            g_selected_app = (g_selected_app - 1 + MAX_APPS) % MAX_APPS;
            break;
        case 'd':
            g_ring_rotation += 15.0f;
            g_selected_app = (g_selected_app + 1) % MAX_APPS;
            break;
        case '\n':
            jetson_app_launch(g_selected_app);
            break;
    }
}

static void jetson_app_launch(int app_id) {
    switch (app_id) {
        case 0: jetson_file_browser_main(); break;
        case 1: jetson_system_info_main(); break;
        case 2: jetson_terminal_main(); break;
        case 3: jetson_about_main(); break;
    }
    jetson_desktop_init();
}

void jetson_desktop_main_loop(void) {
    jetson_desktop_init();
    
    while (1) {
        jetson_desktop_update();
        jetson_desktop_render();
        
        uint8_t key = jetson_keyboard_read_async();
        if (key != 0) {
            jetson_desktop_input(key);
        }
        
        jetson_sleep_ms(FRAME_TIME_MS);
    }
}
