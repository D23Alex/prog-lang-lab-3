#include <stdint.h>

//TODO: учесть пиксель
uint8_t get_padding(uint32_t width) {
    uint8_t padding = 0;
    while ((width + padding) % 4 != 0) {
        padding ++;
    }
    return padding;
}

