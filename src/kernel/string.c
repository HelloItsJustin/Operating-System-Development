#include "string.h"

char* strcpy(char* dest, const char* src) {
    char* r = dest;
    while ((*dest++ = *src++));
    return r;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

uint32_t strlen(const char* str) {
    const char* s = str;
    while (*s) s++;
    return s - str;
}