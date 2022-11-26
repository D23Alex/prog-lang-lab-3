#include <stdio.h>

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
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

//TODO: решить, что возвращать в случае ошибки
FILE* open_bmp(FILE* file, struct image const* img) {
    file = fopen("imageToOpen.bmp", "r");
    if (file == NULL) {
        int status = OPEN_ERROR;
        printf("Error! Status: %d", status);
        return file;
    } else {
        int status = OPEN_OK;
        printf("File was opened successfully! Status: %d", status);
        return file;
    }
}

enum close_status close_bmp(FILE* file, struct image const* img) {
    if (fclose(file)== EOF) {
        int status = CLOSE_ERROR;
        printf("An error occurred while closing the file! Status: %d", status);
    } else {
        int status = CLOSE_OK;
        printf("File was closed successfully! Status: %d", status);
        return status;
    }
}

//TODO: сделать функцию чтения заголовков bmp-файла
enum read_status from_bmp( FILE* in, struct image* img ) {

}

enum write_status to_bmp( FILE* out, struct image const* img ) {

}