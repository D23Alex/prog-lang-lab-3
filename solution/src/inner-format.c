#include <stdint.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};

