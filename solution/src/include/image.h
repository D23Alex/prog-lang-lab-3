#include <stdint.h>

typedef struct image {
    uint64_t width, height;
    struct pixel* data;
} image;

typedef struct pixel {
    uint8_t b, g, r;
} pixel;