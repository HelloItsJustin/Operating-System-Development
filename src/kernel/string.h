#pragma once
#include <stdint.h>

void* memset(void* s, int c, uint32_t n);
void* memcpy(void* dest, const void* src, uint32_t n);
int memcmp(const void* s1, const void* s2, uint32_t n);
char* strcpy(char* dest, const char* src);
int strcmp(const char* s1, const char* s2);
uint32_t strlen(const char* str);