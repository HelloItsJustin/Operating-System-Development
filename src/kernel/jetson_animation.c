#include "jetson_animation.h"
#include "jetson_utils.h"
#include "jetson_vga_wrapper.h"
#include <arch/i686/io.h>

static particle_t g_particles[MAX_PARTICLES];
static int g_particle_count = 0;
static animation_frame_t g_anim_frame = {0};

// Tick counter with busy-wait fallback
static volatile uint32_t g_ticks = 0;
static uint32_t g_boot_start_time = 0;

void jetson_tick_increment(void) {
    g_ticks++;
}

uint32_t jetson_get_ticks(void) {
    // If ticks not advancing, use busy-wait counter as fallback
    static uint32_t fallback_ticks = 0;
    if (g_ticks == 0) {
        fallback_ticks++;
        if (fallback_ticks % 1000000 == 0) {
            return fallback_ticks / 1000000;  // Convert to milliseconds approximately
        }
        return 0;
    }
    return g_ticks;
}

void jetson_sleep_ms(uint32_t ms) {
    // Simple busy-wait (sufficient for boot sequence)
    for (volatile uint32_t i = 0; i < ms * 100000; i++);
}

void jetson_particle_init(void) {
    g_particle_count = 0;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        g_particles[i].lifetime = 0;
        g_particles[i].age = 0;
    }
}

void jetson_particle_emit(int x, int y, int vx, int vy, char glyph, vga_color_t color, uint32_t lifetime) {
    if (g_particle_count >= MAX_PARTICLES) return;
    
    particle_t* p = &g_particles[g_particle_count++];
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    p->glyph = glyph;
    p->color = color;
    p->lifetime = lifetime;
    p->age = 0;
}

void jetson_particle_update(uint32_t delta_ms) {
    for (int i = 0; i < g_particle_count; i++) {
        particle_t* p = &g_particles[i];
        p->age += delta_ms;
        
        if (p->age >= p->lifetime) {
            // Remove particle
            g_particles[i] = g_particles[--g_particle_count];
            i--;
            continue;
        }
        
        // Physics
        p->x += (p->vx * delta_ms) / 1000;
        p->y += (p->vy * delta_ms) / 1000;
        
        // Bounds check (80x25 VGA screen)
        if (p->x < 0 || p->x >= 80 || p->y < 0 || p->y >= 25) {
            g_particles[i] = g_particles[--g_particle_count];
            i--;
        }
    }
}

void jetson_particle_render(void) {
    for (int i = 0; i < g_particle_count; i++) {
        particle_t* p = &g_particles[i];
        VGA_putc(p->x, p->y, p->glyph, p->color, JETSON_BG);
    }
}

void jetson_animation_init(void) {
    g_anim_frame.start_tick = 0;
    g_anim_frame.duration = BOOT_DURATION_MS;
    g_anim_frame.state = JETSON_STATE_BOOT;
    g_anim_frame.progress = 0.0f;
    g_boot_start_time = 0;
    jetson_particle_init();
}

void jetson_animation_update(uint32_t delta_ms) {
    // Use elapsed time directly instead of tick counter
    g_boot_start_time += delta_ms;
    g_anim_frame.progress = (float)g_boot_start_time / (float)g_anim_frame.duration;
    
    if (g_anim_frame.progress >= 1.0f) {
        g_anim_frame.progress = 1.0f;
        if (g_anim_frame.state == JETSON_STATE_BOOT) {
            g_anim_frame.state = JETSON_STATE_DESKTOP;
        }
    }
    
    jetson_particle_update(delta_ms);
}

jetson_state_t jetson_animation_get_state(void) {
    return g_anim_frame.state;
}

float jetson_animation_get_progress(void) {
    return g_anim_frame.progress;
}

static const char* g_jetson_logo[] = {
    "  JETSON OS v1.0",
    "  ===============",
    "",
    "  Cyberpunk-Inspired",
    "  Futuristic Desktop",
};

#define LOGO_LINES 5

void jetson_boot_sequence_start(void) {
    VGA_clrscr();
    jetson_animation_init();
}

void jetson_boot_sequence_update(void) {
    jetson_animation_update(FRAME_TIME_MS);
}

void jetson_boot_sequence_render(void) {
    // Clear center area only, not entire screen
    jetson_vga_clear_rect(0, 4, 79, 22, JETSON_BG);
    
    float progress = jetson_animation_get_progress();
    
    if (progress < 0.2f) {
        jetson_render_title_burst(progress / 0.2f);
    } else if (progress < 0.5f) {
        jetson_render_memory_sequence((progress - 0.2f) / 0.3f);
    } else if (progress < 0.8f) {
        jetson_render_logo_sequence((progress - 0.5f) / 0.3f);
    } else {
        jetson_render_init_messages((progress - 0.8f) / 0.2f);
    }
    
    jetson_particle_render();
}

void jetson_render_title_burst(float phase) {
    int cx = 40, cy = 12;
    const char* title = "JETSON OS";
    int title_len = 9;
    
    int start_x = cx - (title_len / 2);
    for (int i = 0; i < title_len; i++) {
        char c = title[i];
        vga_color_t color = (i % 2 == 0) ? JETSON_PRIMARY : JETSON_ACCENT;
        
        if (phase >= (float)i / title_len) {
            VGA_putc(start_x + i, cy, c, color, JETSON_BG);
            
            int particle_count = (int)(4.0f * phase);
            for (int p = 0; p < particle_count; p++) {
                float angle = (6.28f * p) / 4.0f;
                int vx = (int)(2.0f * cosf(angle) * 100);
                int vy = (int)(2.0f * sinf(angle) * 100);
                jetson_particle_emit(
                    start_x + i, cy,
                    vx, vy,
                    '*', JETSON_ACCENT,
                    500
                );
            }
        }
    }
}

void jetson_render_memory_sequence(float phase) {
    int bar_x = 10, bar_y = 10;
    int bar_width = 60;
    
    VGA_write(bar_x, bar_y - 2, "MEMORY DETECTED:", JETSON_PRIMARY, JETSON_BG);
    
    int filled = (int)(bar_width * phase);
    for (int i = 0; i < bar_width; i++) {
        char c = (i < filled) ? '#' : '-';
        vga_color_t color = (i < filled) ? JETSON_SUCCESS : JETSON_ACCENT;
        VGA_putc(bar_x + i, bar_y, c, color, JETSON_BG);
    }
    
    VGA_write(bar_x, bar_y + 2, "256 MB", JETSON_TEXT, JETSON_BG);
}

void jetson_render_logo_sequence(float phase) {
    int logo_y = 5;
    vga_color_t color = phase < 0.5f ? JETSON_PRIMARY : JETSON_ACCENT;
    
    for (int i = 0; i < LOGO_LINES; i++) {
        int x = 32;
        VGA_write(x, logo_y + i, g_jetson_logo[i], color, JETSON_BG);
    }
}

void jetson_render_init_messages(float phase) {
    int msg_y = 15;
    const char* messages[] = {
        "INITIALIZING KERNEL...",
        "LOADING ORBITAL DESKTOP...",
        "READY FOR COMMANDS",
    };
    
    for (int i = 0; i < 3; i++) {
        if (phase >= (float)i / 3.0f) {
            vga_color_t color = (i == 2) ? JETSON_SUCCESS : JETSON_PRIMARY;
            VGA_write(20, msg_y + i * 2, messages[i], color, JETSON_BG);
        }
    }
}
