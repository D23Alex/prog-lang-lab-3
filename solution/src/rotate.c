#include <include/image.h>
#include <stdlib.h>

struct image rotate(struct image* source ) {
    image result = create_image(source -> height, source -> width);

    result . height = source -> width;
    result . width = source -> height;

    result . data = malloc(result . height * result.width * sizeof(pixel));

    for (uint64_t y = 0; y < source -> height; y++) {
        for (uint64_t x = 0; x < source -> width; x++) {
            /*
             * something similar happened with access to an element of a two-dimensional array
             */
            pixel sourcePixel = source -> data[x + y * source -> height];
            result . data[source -> height * x + (source -> width - y -1)] = sourcePixel;
        }
    }
    return result;
}