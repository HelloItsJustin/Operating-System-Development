#pragma once
#include "jetson_types.h"

void jetson_terminal_main(void);
void jetson_terminal_init(void);
void jetson_terminal_update(void);
void jetson_terminal_render(void);
void jetson_terminal_input(char key);
void jetson_terminal_execute_command(const char* cmd);
