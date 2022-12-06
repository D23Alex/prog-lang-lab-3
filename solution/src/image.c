#include <stdint.h>
#include <stdlib.h>
#include <include/image.h>

//FIXME: учесть пиксель
uint8_t get_padding(uint32_t width) {
    uint8_t padding = 0;
    while ((width + padding) % 4 != 0) {
        padding ++;
    }
    return padding;
}

struct image create_image(uint64_t height, uint64_t width) {
    image image = {
            width = width,
            height = height
    };

    void* data = malloc(width * height * (sizeof(struct pixel)));

    if (data == NULL) {
        return ((struct image) {
            0, 0, 0 //some kind of error code
        });
    } else {
       image.data = data;
        return image;
    }
}

