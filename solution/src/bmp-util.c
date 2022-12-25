#include <include/bmp-util.h>
#include <stdio.h>
#include <stdlib.h>


header read_header(FILE* in) {
    bmp_header bmpHeader;
    if (fread(&bmpHeader, sizeof(bmpHeader), 1, in) != 1) {
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
    bmpHeader.bfileSize = sizeof(bmp_header) + height * (width * sizeof(pixel) + padding);
    bmpHeader.bfReserved = 0;
    bmpHeader.bOffBits = sizeof(bmp_header);
    bmpHeader.biSize = 40;
    bmpHeader.biWidth = width;
    bmpHeader.biHeight = height;
    bmpHeader.biPlanes = 1;
    bmpHeader.biBitCount = 24;
    bmpHeader.biCompression = 0;
    bmpHeader.biSizeImage = 0;
    bmpHeader.biXPelsPerMeter = 0;
    bmpHeader.biYPelsPerMeter = 0;
    bmpHeader.biClrUsed = 0;
    bmpHeader.biClrImportant = 0;
    return bmpHeader;
}

enum read_status from_bmp(FILE* in, image* img) {
    bmp_header bmpHeader;
    header bmpHeaderShell;
    bmpHeaderShell = read_header(in);

    if (!bmpHeaderShell.valid)
        return READ_INVALID_HEADER;

    bmpHeader = bmpHeaderShell.bmpHeader;
    *img = create_image(bmpHeader.biWidth, bmpHeader.biHeight);
    if (fseek(in, bmpHeader.bOffBits, SEEK_SET) != 0)
        return READ_INVALID_SIGNATURE;

    if (bmpHeader.biBitCount != 24)
        return READ_INVALID_BITS;

    uint8_t padding = get_padding(bmpHeader.biWidth);
    struct pixel *data = img->data;
    size_t bytesInRow = sizeof(pixel) * bmpHeader.biWidth + padding;
    for (uint32_t y = 0; y < bmpHeader.biHeight; y++, data += img->width) {
        size_t bytesRead = fread(data, 1, bytesInRow, in);
        if (bytesRead != bytesInRow)
            return READ_INVALID_BITS;
    }
    return READ_OK;
}

enum write_status to_bmp(FILE* out, image* img) {
    bmp_header bmpHeader = set_header(img->width, img->height);
    if (fwrite(&bmpHeader, sizeof(bmpHeader), 1, out) != 1)
        return WRITE_ERROR;

    uint8_t padding = get_padding(bmpHeader.biWidth);
    struct pixel *data = img->data;
    size_t bytesInRow = sizeof(pixel) * bmpHeader.biWidth + padding;
    for (uint32_t y = 0; y < bmpHeader.biHeight; y++, data+= img->width) {
        if (fwrite(data, 1, bytesInRow, out) != bytesInRow) {
            puts("An error occurred while writing bmp image data!");
            return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}
