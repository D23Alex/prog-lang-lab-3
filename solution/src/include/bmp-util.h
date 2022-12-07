#include <stdint-gcc.h>
#include <include/image.h>

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_HEADER,
    READ_INVALID_BITS,
    READ_INVALID_IMG
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

FILE* open_bmp(char* fileName, char* openMode);
enum close_status close_bmp(FILE* in);
struct header read_header(FILE* in);
struct bmp_header set_header(uint64_t width, uint64_t height);
enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image* img );