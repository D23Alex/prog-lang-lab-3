#include <include/image.h>
#include <stdlib.h>


image rotate(image source ) {
    image result = create_image(source.height, source.width);
    for (uint64_t y = 0; y < source.height; y++)
        for (uint64_t x = 0; x < source.width; x++) {
            pixel sourcePixel = source.data[x + y * source.width];
            size_t resultPixelX = source.height - 1 - y;
            size_t resultPixelY = x;
            result.data[resultPixelY * result.width + resultPixelX] = sourcePixel;
        }
    return result;
}
