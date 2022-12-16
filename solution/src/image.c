#include <stdint.h>
#include <stdlib.h>
#include <include/image.h>

uint8_t get_padding(uint32_t width) {
    uint8_t padding = 0;
    while ((width + padding) % 4 != 0) {
        padding ++;
    }
    return padding;
}

image * create_image(uint64_t height, uint64_t width) {
    image* plainImage = malloc(sizeof(image));

    plainImage -> width = width;
    plainImage -> height = height;

    void* data = malloc(sizeof(pixel) * width * height);

    if (data == NULL) {
        image* brokenImage = NULL;
        return brokenImage;
    } else {
        plainImage -> data = data;
        return plainImage;
    }

}

