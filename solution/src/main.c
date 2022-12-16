#include <stdio.h>
#include <include/bmp-util.h>
#include <include/rotate.h>
#include <stdlib.h>

int main( int  argc, char** argv ) {
//    if (argc != 3) {
//        return -1;
//    }

    image * plainImage = create_image(0, 0);


    char * filePath = "C:\\Users\\chesn\\CLionProjects\\assignment-3-image-rotation\\solution\\src\\input.bmp";
    FILE* bmpImage = open_bmp(filePath, "rb");

    if ((int) bmpImage == 0xDEAD) {
        puts("Cannot read a file!");
        exit(-2);
    }

    int status = from_bmp(bmpImage, plainImage);
    if (status != READ_OK) {
        printf("An error occurred while opening the BMP file! Reason: %d", status);
        exit(-2);
    }

    char* outputFilePath = "C:\\Users\\chesn\\CLionProjects\\assignment-3-image-rotation\\solution\\src\\output.bmp";
    image* rotatedImage = rotate(plainImage);
    FILE* fileRotated = open_bmp(outputFilePath, "r+");
    to_bmp(fileRotated, rotatedImage);

    close_bmp(bmpImage);
    close_bmp(fileRotated);

    return 0;
}
