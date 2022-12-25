#include <include/bmp-util.h>
#include <include/rotate.h>
#include <stdio.h>
#include <stdlib.h>


void describe_read_status(enum read_status status) {
    if (status == READ_OK)
        fprintf(stdout, "All good");
    else
        fprintf(stdout, "Some wrong");
}

void describe_write_status(enum write_status status) {
    if (status == WRITE_OK)
        fprintf(stdout, "All good");
    else
        fprintf(stdout, "Some wrong");
}

int main(int  argc, char** argv ) {
    if (argc != 3) {
        fprintf(stderr, "Some wrong");
        return -1;
    }

    image plainImage;
    char * filePath = argv[1];
    FILE * bmpImage = fopen(filePath, "rb");
    if (bmpImage == NULL)
        return -1;

    enum read_status readStatus = from_bmp(bmpImage, &plainImage);
    if (readStatus != READ_OK) {
        fprintf(stderr,"An error occurred while opening the BMP file! Reason:");
        describe_read_status(readStatus);
        exit(-2);
    }

    image rotatedImage = rotate(plainImage);

    FILE* fileRotated = fopen(argv[2], "wb");
    if (fileRotated == NULL)
        return -1;

    enum write_status writeStatus = to_bmp(fileRotated, &rotatedImage);
    if (writeStatus != WRITE_OK) {
        fprintf(stderr,"An error occurred while writing to BMP file! Reason:");
        describe_write_status(writeStatus);
        exit(-2);
    }

    fclose(bmpImage);
    fclose(fileRotated);
    free_image(&plainImage);
    free_image(&rotatedImage);
    return 0;
}
