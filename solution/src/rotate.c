#include <include/image.h>
#include <stdlib.h>

image* rotate(image* source ) {
    image * result = create_image(source -> height, source -> width);

    result -> height = source -> width;
    result -> width = source -> height;

    result -> data = malloc(result -> height * result -> width * sizeof(pixel));

    //something similar happened with access to an element of a two-dimensional array
    for (uint64_t y = 0; y < source -> height; y++) {
        for (uint64_t x = 0; x < source -> width; x++) {
            pixel sourcePixel = source -> data[x + y * source -> height];
            result -> data[source -> height * x + (source -> width - y -1)] = sourcePixel;
        }
    }
    return result;
}