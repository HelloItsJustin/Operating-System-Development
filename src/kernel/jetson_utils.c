#include "jetson_utils.h"
#include <stdarg.h>

int strlen_safe(const char* str, size_t max_len) {
    if (!str) return 0;
    int len = 0;
    while (str[len] && len < max_len) len++;
    return len;
}

int strcmp_safe(const char* a, const char* b, size_t max_len) {
    if (!a || !b) return (a == b) ? 0 : -1;
    for (size_t i = 0; i < max_len; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
        if (a[i] == 0) return 0;
    }
    return 0;
}

char* strcpy_safe(char* dst, const char* src, size_t max_len) {
    if (!dst || !src) return dst;
    size_t i = 0;
    while (src[i] && i < max_len - 1) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
    return dst;
}

void* memset_safe(void* ptr, int value, size_t len) {
    uint8_t* p = (uint8_t*)ptr;
    for (size_t i = 0; i < len; i++) {
        p[i] = value;
    }
    return ptr;
}

void* memcpy_safe(void* dst, const void* src, size_t len) {
    uint8_t* d = (uint8_t*)dst;
    const uint8_t* s = (const uint8_t*)src;
    for (size_t i = 0; i < len; i++) {
        d[i] = s[i];
    }
    return dst;
}

void itoa(int num, char* buf, int radix) {
    if (num == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return;
    }
    
    int is_negative = num < 0;
    if (is_negative) num = -num;
    
    int pos = 0;
    while (num > 0) {
        int digit = num % radix;
        buf[pos++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
        num /= radix;
    }
    
    if (is_negative) buf[pos++] = '-';
    buf[pos] = 0;
    
    // Reverse string
    for (int i = 0; i < pos / 2; i++) {
        char temp = buf[i];
        buf[i] = buf[pos - 1 - i];
        buf[pos - 1 - i] = temp;
    }
}

void utoa(unsigned int num, char* buf, int radix) {
    if (num == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return;
    }
    
    int pos = 0;
    while (num > 0) {
        int digit = num % radix;
        buf[pos++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
        num /= radix;
    }
    buf[pos] = 0;
    
    for (int i = 0; i < pos / 2; i++) {
        char temp = buf[i];
        buf[i] = buf[pos - 1 - i];
        buf[pos - 1 - i] = temp;
    }
}

int sprintf_safe(char* buf, size_t buf_size, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    int written = 0;
    while (*fmt && written < buf_size - 1) {
        if (*fmt == '%' && *(fmt + 1)) {
            fmt++;
            switch (*fmt) {
                case 'd': {
                    int val = va_arg(args, int);
                    char num_buf[16];
                    itoa(val, num_buf, 10);
                    int len = strlen_safe(num_buf, 16);
                    strcpy_safe(buf + written, num_buf, buf_size - written);
                    written += len;
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    int len = strlen_safe(str, buf_size - written);
                    strcpy_safe(buf + written, str, buf_size - written);
                    written += len;
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    char num_buf[16];
                    utoa(val, num_buf, 16);
                    int len = strlen_safe(num_buf, 16);
                    strcpy_safe(buf + written, num_buf, buf_size - written);
                    written += len;
                    break;
                }
                case '%':
                    buf[written++] = '%';
                    break;
            }
            fmt++;
        } else {
            buf[written++] = *fmt++;
        }
    }
    buf[written] = 0;
    va_end(args);
    return written;
}

// Fast cosine approximation using Taylor series
float cosf(float x) {
    // Normalize to [-pi, pi]
    const float pi = 3.14159265359f;
    while (x > pi) x -= 2 * pi;
    while (x < -pi) x += 2 * pi;
    
    float result = 1.0f;
    float term = 1.0f;
    for (int i = 1; i < 10; i++) {
        term *= -x * x / ((2 * i - 1) * (2 * i));
        result += term;
    }
    return result;
}

// Fast sine approximation using Taylor series
float sinf(float x) {
    const float pi = 3.14159265359f;
    while (x > pi) x -= 2 * pi;
    while (x < -pi) x += 2 * pi;
    
    float result = x;
    float term = x;
    for (int i = 1; i < 10; i++) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        result += term;
    }
    return result;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

float fabs(float x) {
    return x < 0.0f ? -x : x;
}

uint32_t crc32(const uint8_t* data, size_t len) {
    uint32_t crc = 0xffffffff;
    
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ ((crc & 1) ? 0xedb88320 : 0);
        }
    }
    
    return crc ^ 0xffffffff;
}
