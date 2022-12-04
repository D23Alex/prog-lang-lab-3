#include <stdio.h>
#include <stdlib.h>
#include <include/bmp.h>
#include <include/image.h>
#include <include/rotate.h>

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

//TODO: на открытых файлах они могут запускать from_bmp и to_bmp?
enum open_status open_bmp(FILE* file) {
    if (fopen((const char *) file, "r+") != NULL) {
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

enum read_status from_bmp( FILE* in, struct image* img ) {
    if (img == NULL) {
        return READ_INVALID_IMG;
    } else {
       struct header header = read_header(in);
       if (header.valid != 1) {
           return READ_INVALID_HEADER;
       } else {
           bmp_header bmpHeader = header.bmpHeader;

           img = create_image(header.bmpHeader.biHeight, header.bmpHeader.biWidth);
           uint8_t padding = get_padding(img -> width);
           for (int offset = 0; offset < img -> width * img -> height; offset++) {
               fread(img -> data + offset, sizeof (struct pixel), 1, in);
               //FIXME
               img -> data += padding;
           }
           return READ_OK;
       }
    }
}
//FIXME: файл нужно открыть
enum write_status to_bmp( FILE* out, struct image* img ) {
    bmp_header bmpHeader = set_header(img->width, img ->height);

    int padding = get_padding(img -> width);

    int writeStatus = fwrite(&bmpHeader, sizeof (struct bmp_header), 1, out);
    if (!writeStatus) {
        return WRITE_ERROR;
    } else {
        writeStatus = fseek(out, bmpHeader.bOffBits, SEEK_SET);
        if (writeStatus) {
            return WRITE_ERROR;
        } else {
            for (uint64_t i = 0; i < img -> height; i++) {
                uint64_t size = sizeof (struct pixel) * img -> width;
                struct pixel * bitmapArray  = img -> data + img -> width * i;
                writeStatus = fwrite(bitmapArray, size, 1, out);
                if (!writeStatus) {
                    return WRITE_ERROR;
                } else {
                    writeStatus = fwrite(img -> data, padding, 1, out);
                    if (padding != 0 && !writeStatus) {
                        return WRITE_ERROR;
                    }
                }
            }
        }
    }
    return WRITE_OK;
}