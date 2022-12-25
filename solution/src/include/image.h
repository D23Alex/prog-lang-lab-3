#include <stddef.h>
#include <stdint.h>


typedef struct pixel {
    uint8_t b, g, r;
} pixel;

typedef struct image {
    uint64_t width, height;
    pixel* data;
} image;

uint8_t get_padding(uint32_t width);
image create_image(uint64_t width, uint64_t height);
void free_image(struct image *image);
