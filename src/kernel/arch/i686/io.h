#pragma once
#include <stdint.h>

// Assembly function declarations
void __attribute__((cdecl)) i686_outb(uint16_t port, uint8_t value);
uint8_t __attribute__((cdecl)) i686_inb(uint16_t port);
uint8_t __attribute__((cdecl)) i686_EnableInterrupts();
uint8_t __attribute__((cdecl)) i686_DisableInterrupts();
void i686_iowait();
void __attribute__((cdecl)) i686_Panic();

// ✅ Inline wrappers for portability and cleaner usage
static inline void outb(uint16_t port, uint8_t value) {
    i686_outb(port, value);
}

static inline uint8_t inb(uint16_t port) {
    return i686_inb(port);
}