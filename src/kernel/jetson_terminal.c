#include "jetson_terminal.h"
#include "jetson_keyboard.h"
#include "jetson_animation.h"
#include "jetson_utils.h"
#include "jetson_vga_wrapper.h"

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 25
#define COMMAND_HISTORY 10
#define INPUT_BUFFER 256

typedef struct {
    char buffer[INPUT_BUFFER];
    int length;
    int cursor_pos;
} terminal_input_t;

static terminal_input_t g_input = {0};
static char g_output[2048] = {0};
static int g_output_lines = 0;
static uint32_t g_cursor_blink = 0;
static int g_terminal_exit = 0;

static void jetson_terminal_print(const char* text);

void jetson_terminal_main(void) {
    jetson_terminal_init();
    g_terminal_exit = 0;
    
    while (!g_terminal_exit) {
        jetson_terminal_update();
        jetson_terminal_render();
        
        uint8_t key = jetson_keyboard_read_async();
        if (key == 27) g_terminal_exit = 1;  // ESC to exit
        if (key != 0) {
            jetson_terminal_input(key);
        }
        
        jetson_sleep_ms(50);
    }
}

void jetson_terminal_init(void) {
    VGA_clrscr();
    g_input.length = 0;
    g_input.cursor_pos = 0;
    g_output_lines = 0;
    
    jetson_terminal_print("JETSON OS v1.0 - COMMAND TERMINAL\n");
    jetson_terminal_print("Type 'help' for commands\n");
    jetson_terminal_print("\n");
}

void jetson_terminal_update(void) {
    g_cursor_blink = (jetson_get_ticks() / 250) % 2;
}

void jetson_terminal_render(void) {
    VGA_clrscr();
    
    VGA_write(0, 0, "JETSON TERMINAL", JETSON_PRIMARY, JETSON_BG);
    VGA_putc(79, 0, 'X', JETSON_ACCENT, JETSON_BG);
    
    // Display output area
    int line = 1;
    int output_len = strlen_safe(g_output, 2048);
    const char* p = g_output;
    
    while (*p && line < 23) {
        char line_buffer[TERMINAL_WIDTH + 1] = {0};
        int x = 0;
        
        while (*p && *p != '\n' && x < TERMINAL_WIDTH) {
            line_buffer[x++] = *p++;
        }
        if (*p == '\n') p++;
        
        VGA_write(0, line, line_buffer, JETSON_TEXT, JETSON_BG);
        line++;
    }
    
    // Draw input line
    VGA_write(0, 23, "> ", JETSON_PRIMARY, JETSON_BG);
    VGA_write(2, 23, g_input.buffer, JETSON_TEXT, JETSON_BG);
    
    // Draw cursor
    if (g_cursor_blink) {
        VGA_putc(2 + g_input.cursor_pos, 23, '_', JETSON_ACCENT, JETSON_BG);
    }
    
    VGA_write(0, 24, "ESC=Menu | ENTER=Execute | F1=Help", JETSON_ACCENT, JETSON_BG);
}

void jetson_terminal_input(char key) {
    if (key == '\n') {
        jetson_terminal_execute_command(g_input.buffer);
        g_input.length = 0;
        g_input.cursor_pos = 0;
        g_input.buffer[0] = 0;
        
    } else if (key == '\b' && g_input.cursor_pos > 0) {
        g_input.cursor_pos--;
        g_input.length--;
        g_input.buffer[g_input.length] = 0;
        
    } else if (key >= 32 && key < 127 && g_input.length < INPUT_BUFFER - 1) {
        g_input.buffer[g_input.length++] = key;
        g_input.buffer[g_input.length] = 0;
        g_input.cursor_pos++;
    }
}

void jetson_terminal_execute_command(const char* cmd) {
    char echo[INPUT_BUFFER + 4] = {0};
    sprintf_safe(echo, sizeof(echo), "> %s\n", cmd);
    jetson_terminal_print(echo);
    
    if (strcmp_safe(cmd, "help", 256) == 0) {
        jetson_terminal_print("Available commands:\n");
        jetson_terminal_print("  help  - Show this help\n");
        jetson_terminal_print("  clear - Clear terminal\n");
        jetson_terminal_print("  mem   - Show memory info\n");
        jetson_terminal_print("  cpu   - Show CPU info\n");
        jetson_terminal_print("  exit  - Return to desktop\n");
    } else if (strcmp_safe(cmd, "clear", 256) == 0) {
        g_output[0] = 0;
        g_output_lines = 0;
    } else if (strcmp_safe(cmd, "mem", 256) == 0) {
        jetson_terminal_print("Memory: 128MB/512MB (25% used)\n");
    } else if (strcmp_safe(cmd, "cpu", 256) == 0) {
        jetson_terminal_print("CPU: 5% | Processes: 12\n");
    } else if (strcmp_safe(cmd, "exit", 256) == 0) {
        g_terminal_exit = 1;
    } else if (strlen_safe(cmd, 256) > 0) {
        jetson_terminal_print("Command not found\n");
    }
    
    jetson_terminal_print("\n");
}

static void jetson_terminal_print(const char* text) {
    size_t text_len = strlen_safe(text, 256);
    size_t current_len = strlen_safe(g_output, 2048);
    
    if (current_len + text_len < 2048) {
        strcpy_safe(g_output + current_len, text, 2048 - current_len);
    }
}
