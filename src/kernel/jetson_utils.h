#pragma once
#include <stddef.h>
#include <stdint.h>

// String utilities
int strlen_safe(const char* str, size_t max_len);
int strcmp_safe(const char* a, const char* b, size_t max_len);
char* strcpy_safe(char* dst, const char* src, size_t max_len);
void* memset_safe(void* ptr, int value, size_t len);
void* memcpy_safe(void* dst, const void* src, size_t len);

// Formatting
int sprintf_safe(char* buf, size_t buf_size, const char* fmt, ...);
void itoa(int num, char* buf, int radix);
void utoa(unsigned int num, char* buf, int radix);

// Math
float cosf(float x);
float sinf(float x);
int abs(int x);
float fabs(float x);

// Checksums
uint32_t crc32(const uint8_t* data, size_t len);
