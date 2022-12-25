#include <bits/types/FILE.h>
#include <include/bmp.h>
#include <include/image.h>

typedef struct header {
    bmp_header bmpHeader;
    int valid;
} header;

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_HEADER,
    READ_INVALID_BITS,
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

header read_header(FILE* in);
bmp_header set_header(uint64_t width, uint64_t height);
enum read_status from_bmp( FILE* in, image* img );
enum write_status to_bmp( FILE* out, image* img );
