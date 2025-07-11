#include <stdint.h>
#include "stdio.h"
#include "x86.h"
#include "disk.h"
#include "fat.h"
#include "memdefs.h"
#include "memory.h"
#include "mbr.h"
#include "stdlib.h"
#include "string.h"
#include "elf.h"
#include "memdetect.h"
#include <boot/bootparams.h>

uint8_t* KernelLoadBuffer = (uint8_t*)MEMORY_LOAD_KERNEL;
uint8_t* Kernel = (uint8_t*)MEMORY_KERNEL_ADDR;

BootParams g_BootParams;

typedef void (*KernelStart)(BootParams* bootParams);

void __attribute__((cdecl)) start(uint16_t bootDrive, void* partition)
{
    // RAW VGA test to confirm stage2 is reached
    volatile char* video = (volatile char*)0xB8000;
    video[0] = 'J';
    video[1] = 0x07;
    video[2] = 'O';
    video[3] = 0x07;

    // Simple print to check printf is working
    printf("Stage 2: Bootloader started\n");

    DISK disk;
    if (!DISK_Initialize(&disk, bootDrive))
    {
        printf("Disk init error\n");
        goto end;
    }

    Partition part;
    MBR_DetectPartition(&part, &disk, partition);

    if (!FAT_Initialize(&part))
    {
        printf("FAT init error\n");
        goto end;
    }

    // prepare boot params
    g_BootParams.BootDevice = bootDrive;
    Memory_Detect(&g_BootParams.Memory);

    printf("Boot device: 0x%x\n", g_BootParams.BootDevice);
    printf("Memory regions: %d\n", g_BootParams.Memory.RegionCount);

    for (int i = 0; i < g_BootParams.Memory.RegionCount; i++)
    {
        printf("Region %d: start=0x%llx, length=0x%llx, type=%x\n",
               i,
               g_BootParams.Memory.Regions[i].Begin,
               g_BootParams.Memory.Regions[i].Length,
               g_BootParams.Memory.Regions[i].Type);
    }

    // Load kernel
    KernelStart kernelEntry;
    if (!ELF_Read(&part, "/boot/kernel.elf", (void**)&kernelEntry))
    {
        printf("ELF read failed. Halting.\n");
        goto end;
    }

    printf("Kernel loaded. Jumping to kernel...\n");

    // Jump to kernel
    kernelEntry(&g_BootParams);

end:
    for (;;);
}