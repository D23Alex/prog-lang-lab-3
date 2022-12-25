#include <include/image.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint8_t get_padding(uint32_t width) {
    uint32_t bytes_per_row = width * sizeof(struct pixel);
    return (4 - (bytes_per_row % 4)) % 4;
}

void free_image(struct image *image) {
    free(image->data);
    image->data = NULL;
}

image create_image(uint64_t width, uint64_t height) {
    struct image new_image = (struct image) {.width = width, .height = height, .data = NULL};
    new_image.data = malloc(sizeof(struct pixel) * new_image.height * new_image.width);
    if (new_image.data == NULL) {
        fprintf(stderr, "FATAL - Could not allocate");
        abort();
    }
    return new_image;
}
