#include <stdio.h>
#include <stdlib.h>
#include <include/bmp-util.h>

#define OPEN_ERROR_CODE 0xDEAD

FILE* open_bmp(const char* fileName, char* openMode) {
    FILE* file;
    file = fopen(fileName, openMode);
    if (file != NULL ) {
        return file;
    } else {
        return (FILE *) OPEN_ERROR_CODE;
    }
}

enum close_status close_bmp(FILE* in) {
    if (fclose(in) != EOF) {
        return CLOSE_OK;
    }  else {
        return CLOSE_ERROR;
    }
}

header read_header(FILE* in) {
    bmp_header bmpHeader;
    if (fread(&bmpHeader, sizeof bmpHeader, 1, in) != 1) {
        header header = {
                .valid = 0,
                .bmpHeader = bmpHeader
        };
        return header;
    } else {
        header header = {
                .valid = 1,
                .bmpHeader = bmpHeader
        };

        return header;
    }
}

bmp_header set_header(uint64_t width, uint64_t height) {
    int padding = get_padding(width);
    bmp_header bmpHeader;
    bmpHeader.bfType = 0x4D42;
    bmpHeader.bfileSize = width * sizeof(pixel) + sizeof(bmpHeader) + height;
    bmpHeader.bfReserved = 0;
    bmpHeader.bOffBits = 54;
    bmpHeader.biSize = 40;
    bmpHeader.biWidth = width;
    bmpHeader.biHeight = height;
    bmpHeader.biPlanes = 1;
    bmpHeader.biBitCount = 24;
    bmpHeader.biCompression = 0;
    bmpHeader.biSizeImage = (width + padding) * height;
    bmpHeader.biXPelsPerMeter = 0;
    bmpHeader.biYPelsPerMeter = 0;
    bmpHeader.biClrUsed = 0;
    bmpHeader.biClrImportant = 0;
    return bmpHeader;
}

enum read_status from_bmp(FILE* in, image* img) {
    if (img == NULL || ((img->width == 0xDEAD) && (img->height == 0xDEAD))) {
        puts("The input of the function was a broken image!");
        return READ_INVALID_IMG;
    }

    bmp_header bmpHeader;
    header bmpHeaderShell;
    bmpHeaderShell = read_header(in);

    if (bmpHeaderShell.valid) {
        bmpHeader = bmpHeaderShell.bmpHeader;
        img->width = bmpHeader.biWidth;
        img->height = bmpHeader.biHeight;

        img->data = malloc(sizeof (pixel) * img -> width * img -> height);
        if (fseek(in, (long) bmpHeader.bOffBits, SEEK_SET) != 0) {
            return READ_INVALID_SIGNATURE;
        }

        if (bmpHeader.biBitCount != 24) {
            return READ_INVALID_BITS;
        }

        uint8_t padding = get_padding(bmpHeader.biWidth);
        for (uint32_t y = 0; y < bmpHeader.biHeight; y++) {
            if (!fread(img -> data + y * bmpHeader.biWidth, sizeof (pixel) * bmpHeader.biWidth, 1, in)) {
                return READ_INVALID_BITS;
            }
            fseek(in, padding, SEEK_CUR);
        }
    } else {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

//FIXME!!!
//TODO: где нужно освободить память при ошибке?
enum write_status to_bmp(FILE* out, image* img) {
    bmp_header bmpHeader = set_header(img -> width, img->height);
    fwrite(&bmpHeader, sizeof(bmpHeader), 1, out);

    uint8_t padding = get_padding(bmpHeader.biWidth);
    for (uint32_t y = 0; y < bmpHeader.biHeight; y++) {
        if (!fwrite(img -> data + img -> width * y, sizeof(pixel), img->width, out)) {
            puts("An error occurred while writing bmp image data!");
            return WRITE_ERROR;
        }
    }
    puts("The image has been successfully rotated!");
    return WRITE_OK;

}