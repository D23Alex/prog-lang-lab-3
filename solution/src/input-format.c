#include <stdio.h>
#include <stdlib.h>
#include <include/bmp.h>
#include <include/image.h>

typedef struct bmp_header bmp_header;

enum read_status  {
    READ_OK = 0,
    READ_INVALID_HEADER,
    READ_INVALID_IMG
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

struct header {
    int valid;
    bmp_header bmpHeader;
};

//TODO: на открытых файлах они могут запускать from_bmp и to_bmp
enum open_status open_bmp(FILE* in) {
    if (fopen((const char *) in, "rb") != NULL) {
        int status = OPEN_OK;
        return status;
    } else {
        int status = OPEN_ERROR;
        return status;
    }
}

enum close_status close_bmp(FILE* in) {
    if (fclose(in) != EOF) {
        int status = CLOSE_OK;
        return status;
    }  else {
        int status = CLOSE_ERROR;
        return status;
    }
}

struct header read_header(FILE* in) {
    bmp_header bmpHeader;
    if (open_bmp(in) == 0) {
        if (fread(&bmpHeader, sizeof bmpHeader, 1, in) != 1) {
            return (struct header) {
                    .valid = 0,
                    .bmpHeader = bmpHeader
            };
        } else {
            return (struct header) {
                .valid = 1,
                .bmpHeader = bmpHeader
            };
        }
    } else {
        return (struct header) {
            .valid = 0,
        };
    }
};

//FIXME убрать заглушки
struct bmp_header set_header(uint64_t width, uint64_t height) {
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
    bmpHeader.biSizeImage;
    bmpHeader.biXPelsPerMeter = 0;
    bmpHeader.biYPelsPerMeter = 0;
    bmpHeader.biClrUsed = 0;
    bmpHeader.biClrImportant = 0;
    return bmpHeader;

}



enum read_status from_bmp( FILE* in, struct image* img ) {
    if (img == NULL) {
        return READ_INVALID_IMG;
    } else {
       struct header header = read_header(in);
       if (header.valid != 1) {
           return READ_INVALID_HEADER;
       } else {
           bmp_header bmpHeader = header.bmpHeader;

       }
    }
}

enum write_status to_bmp( FILE* out, struct image const* img ) {

}