#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/irq.h>
#include <debug.h>
#include <boot/bootparams.h>
#include <arch/i686/vga_text.h>
#include "jetson_desktop_interactive.h"

extern void _init();


void start(BootParams* bootParams) {
    VGA_clrscr();
    _init();
    HAL_Initialize();

    log_debug("Main", "Boot device: %x", bootParams->BootDevice);
    log_debug("Main", "Memory region count: %d", bootParams->Memory.RegionCount);
    
    for (int i = 0; i < bootParams->Memory.RegionCount; i++) {
        log_debug("Main", "MEM: start=0x%llx length=0x%llx type=%x", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type);
    }

    log_info("Main", "Jetson OS v1.0 Booting...");
    
    // Run boot animation
    jetson_boot_animation();
    
    // Run interactive desktop
    jetson_desktop_interactive();
    
    // Shutdown
    printf("\nSystem halting...\n");
    for (;;);
}