#include <stdint.h>

typedef struct image {
    uint64_t width, height;
    struct pixel* data;
} image;

typedef struct pixel {
    uint8_t b, g, r;
} pixel;

struct image create_image(uint64_t height, const uint64_t width);
uint8_t get_padding(uint32_t width);
