#pragma once
#include "jetson_types.h"

#define MAX_APPS 4

void jetson_desktop_init(void);
void jetson_desktop_update(void);
void jetson_desktop_render(void);
void jetson_desktop_input(char key);
void jetson_desktop_main_loop(void);

// App launchers
void jetson_file_browser_main(void);
void jetson_system_info_main(void);
void jetson_terminal_main(void);
void jetson_about_main(void);
