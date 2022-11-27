#include <stdio.h>
#include <include/bmp.h>

typedef struct bmp_header bmp_header;

enum read_status  {
    READ_OK = 0,
    READ_INVALID_HEADER
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

enum read_status read_header(FILE* in) {
    bmp_header bmpHeader;
    if ((fread(&bmpHeader, sizeof (bmpHeader), 1, in)) != 1) {
        int status = READ_INVALID_HEADER;
        return status;
    } else {
        int status = READ_OK;
        return status;
    }
}

//TODO: сделать здесь открытие файла
//FIXME: CONST VOID
enum write_status write_header(FILE* out, const void *bmpHeader) {
    if ((fwrite(bmpHeader, sizeof(bmpHeader), 1, out)) != 1) {
        int status = WRITE_ERROR;
        return status;
    } else {
        int status = WRITE_OK;
        return status;
    }
}



//TODO: решить, что возвращать в случае ошибки
//FIXME: неправильное открытие файла
FILE* open_bmp(char fileName[]) {
    FILE* bmpImage = fopen(fileName, "rb");
    if (bmpImage == NULL) {
        int status = OPEN_ERROR;
        printf("Error! Status: %d", status);
        return bmpImage;
    } else {
        int status = OPEN_OK;
        printf("File was opened successfully! Status: %d", status);
        return bmpImage;
    }
}

//TODO: для чего нужен второй параметр?
//ANSWER: чтобы туда записывать информацию об изображении!
//TODO: нужно ли проверять, является ли файл формата BMP?
enum close_status close_bmp(FILE* file) {
    if (fclose(file) == EOF) {
        int status = CLOSE_ERROR;
        printf("An error occurred while closing the file! Status: %d", status);
        return status;
    } else {
        int status = CLOSE_OK;
        printf("File was closed successfully! Status: %d", status);
        return status;
    }
}

enum read_status from_bmp( FILE* in, struct image* img ) {

}

enum write_status to_bmp( FILE* out, struct image const* img ) {

}