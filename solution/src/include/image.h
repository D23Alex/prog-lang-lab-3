#include <stdint.h>

typedef struct pixel {
    uint8_t b, g, r;
} pixel;

typedef struct image {
    uint64_t width, height;
    pixel* data;
} image;

struct image* create_image(uint64_t height, uint64_t width);
uint8_t get_padding(uint32_t width);
