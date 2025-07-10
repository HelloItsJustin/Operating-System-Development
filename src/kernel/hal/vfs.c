#include <hal/vfs.h>
#include <stddef.h>
#include <arch/i686/vga_text.h> // ✅ Correct header for VGA_putc()

int VFS_Write(fd_t file, uint8_t* data, size_t size)
{
    if (file == VFS_FD_STDOUT || file == VFS_FD_DEBUG)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (data[i] == '\n') VGA_putc('\r');
            VGA_putc((char)data[i]);
        }
        return (int)size;
    }

    return -1;
}