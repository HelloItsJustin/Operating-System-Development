#include "vfs.h"
#include <arch/i686/vga_text.h>
#include <arch/i686/e9.h>

int VFS_Write(fd_t file, const void* data, size_t size)
{
    const uint8_t* bytes = (const uint8_t*)data;

    switch (file)
    {
    case VFS_FD_STDIN:
        return 0;

    case VFS_FD_STDOUT:
    case VFS_FD_STDERR:
        for (size_t i = 0; i < size; i++)
            VGA_putc(bytes[i]);
        return size;

    case VFS_FD_DEBUG:
        for (size_t i = 0; i < size; i++)
            e9_putc(bytes[i]);
        return size;

    default:
        return -1;
    }
}