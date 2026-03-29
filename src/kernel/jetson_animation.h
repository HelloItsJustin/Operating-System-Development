#pragma once
#include "jetson_types.h"

#define MAX_PARTICLES 128
#define FRAME_TIME_MS 50  // 20 FPS
#define BOOT_DURATION_MS 6000

// Particle System
void jetson_particle_init(void);
void jetson_particle_emit(int x, int y, int vx, int vy, char glyph, vga_color_t color, uint32_t lifetime);
void jetson_particle_update(uint32_t delta_ms);
void jetson_particle_render(void);

// Animation State
void jetson_animation_init(void);
void jetson_animation_update(uint32_t delta_ms);
jetson_state_t jetson_animation_get_state(void);
float jetson_animation_get_progress(void);

// Boot Sequence
void jetson_boot_sequence_start(void);
void jetson_boot_sequence_update(void);
void jetson_boot_sequence_render(void);

// Timing
uint32_t jetson_get_ticks(void);
void jetson_sleep_ms(uint32_t ms);

// Helper rendering functions
void jetson_render_title_burst(float phase);
void jetson_render_memory_sequence(float phase);
void jetson_render_logo_sequence(float phase);
void jetson_render_init_messages(float phase);
