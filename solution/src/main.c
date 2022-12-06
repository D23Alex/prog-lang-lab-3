#include <stdio.h>
#include <include/bmp-util.h>
#include <include/image.h>

int main( int argc, char** argv ) {
    if (argc != 3) {
        return -1;
    }

    image* image;

    FILE *sourceImage;
    sourceImage = (FILE *) open_bmp((FILE *) argv[1]);
    FILE* resultImage;
    resultImage = (FILE *) open_bmp((FILE *) argv[2]);
    enum read_status readStatus = from_bmp(sourceImage, image);

    if(readStatus) {
        printf("Read from file error: %d", readStatus);
        return readStatus;
    }



    return 0;
}
