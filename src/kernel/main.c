#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/irq.h>
#include <debug.h>
#include <boot/bootparams.h>
#include <arch/i686/vga_text.h>

extern void _init();
void crash_me();

// Tic-Tac-Toe game
#include "tic_tac_toe.h"  // Adjust path if needed
void timer(Registers* regs)
{
    printf(".");
}
void delay_seconds(int seconds)
{
    for (int s = 0; s < seconds; s++) {
        for (volatile int i = 0; i < 50000000; ++i);  // Adjust this number for your CPU speed
    }
}
void start(BootParams* bootParams)
{
    VGA_clrscr();       // 👈 clear screen before anything
    _init();            // runtime init

    HAL_Initialize();   // hardware setup

    log_debug("Main", "Boot device: %x", bootParams->BootDevice);
    log_debug("Main", "Memory region count: %d", bootParams->Memory.RegionCount);
    for (int i = 0; i < bootParams->Memory.RegionCount; i++) 
    {
        log_debug("Main", "MEM: start=0x%llx length=0x%llx type=%x", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type);
    }

    log_info("Main", "This is an info msg!");
    log_warn("Main", "This is a warning msg!");
    log_err("Main", "This is an error msg!");
    log_crit("Main", "This is a critical msg!");
    printf("\n");
    printf("=================================================\n");
    printf("             Welcome to Jetson OS v0.2         \n");
    printf("=================================================\n");
    printf("\n");
    printf("\n[Jetson OS v0.2] New: \n 1. PvP Tic-Tac-Toe \n 2. Low-level keyboard input \n 3. Log levels \n 4. VGA screen clear\n");
    printf("\n");
    printf("=================================================\n");
    printf("  Press any key to launch the game...\n");
    printf("=================================================\n");
    while (getchr() == 0);  // Wait until key is pressed

    printf("\nLaunching Tic-Tac-Toe Game...\n");

    tic_tac_toe_main();

    for (;;); // Halt the system after game ends
}