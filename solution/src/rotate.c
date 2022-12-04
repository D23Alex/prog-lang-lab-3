#include <include/image.h>
#include <stdlib.h>

struct image* rotate(struct image* source ) {
    image* result = create_image(source -> height, source -> width);

    for (uint8_t y = 0; y < source -> height; y++) {
        for (uint8_t x = 0; x < source -> width; x++) {
            result -> data[result -> width * x + y] = source -> data[source -> width * (source -> height - y - 1) + x];
        }
    }
    return result;
}