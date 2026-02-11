#include <stdio.h>
#include <stdint.h>
int main() {
    uint32_t x = 1;
    uint8_t *p = (uint8_t *)&x;

    if (*p == 1) {
        puts("Little Endian.");
    } else {
        puts("Big Endian.");
    }
}
