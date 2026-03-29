#pragma once
#include <stdint.h>
#include <stddef.h>

// VGA Color Palette (16 colors)
typedef enum {
    VGACOLOR_BLACK = 0,
    VGACOLOR_BLUE = 1,
    VGACOLOR_GREEN = 2,
    VGACOLOR_CYAN = 3,
    VGACOLOR_RED = 4,
    VGACOLOR_MAGENTA = 5,
    VGACOLOR_BROWN = 6,
    VGACOLOR_LIGHTGRAY = 7,
    VGACOLOR_DARKGRAY = 8,
    VGACOLOR_LIGHTBLUE = 9,
    VGACOLOR_LIGHTGREEN = 10,
    VGACOLOR_LIGHTCYAN = 11,
    VGACOLOR_LIGHTRED = 12,
    VGACOLOR_LIGHTMAGENTA = 13,
    VGACOLOR_YELLOW = 14,
    VGACOLOR_WHITE = 15,
} vga_color_t;

// Jetson Color Scheme
#define JETSON_PRIMARY VGACOLOR_LIGHTCYAN       // 11
#define JETSON_ACCENT VGACOLOR_LIGHTMAGENTA     // 13
#define JETSON_SUCCESS VGACOLOR_LIGHTGREEN      // 10
#define JETSON_ERROR VGACOLOR_LIGHTRED          // 12
#define JETSON_BG VGACOLOR_BLACK                // 0
#define JETSON_TEXT VGACOLOR_WHITE              // 15

// Animation State Machine
typedef enum {
    JETSON_STATE_BOOT,
    JETSON_STATE_LOGO,
    JETSON_STATE_DESKTOP,
    JETSON_STATE_TERMINAL,
} jetson_state_t;

// Particle System
typedef struct {
    int x, y;
    int vx, vy;
    uint32_t lifetime;
    uint32_t age;
    char glyph;
    vga_color_t color;
} particle_t;

// Animation Frame
typedef struct {
    uint32_t start_tick;
    uint32_t duration;
    float progress;
    jetson_state_t state;
} animation_frame_t;

// Orbital Ring App
typedef struct {
    const char* name;
    int angle;
    int radius;
    int id;
    vga_color_t color;
} orbital_app_t;

// Terminal Command
typedef struct {
    char input[256];
    char output[2048];
    uint32_t output_len;
} terminal_cmd_t;
