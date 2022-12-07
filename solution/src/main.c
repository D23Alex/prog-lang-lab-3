#include <stdio.h>
#include <include/bmp-util.h>
#include <include/rotate.h>
#include <stdlib.h>

int main( int argc, char** argv ) {
    if (argc != 3) {
        return -1;
    }

    image plainImage = {
            0, 0, 0
    };

    FILE* bmpImage = open_bmp("input.bmp", "r");
    int status = from_bmp(bmpImage, &plainImage);
    if (status != READ_OK) {
        printf("An error occurred while opening the BMP file! Reason: %d", status);
        exit(-1);
    }

    image rotatedImage = rotate(&plainImage);
    FILE* fileRotated = open_bmp("result.bmp", "w");
    int writeStatus = to_bmp(fileRotated, &rotatedImage);

    return 0;
}
