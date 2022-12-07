#include <stdint-gcc.h>
#include <include/image.h>

enum read_status {
    READ_OK = 0,
    READ_INVALID_HEADER,
    READ_INVALID_IMG
};
enum write_status;
enum open_status;
enum close_status;

enum FILE* open_bmp(char* fileName);
enum close_status close_bmp(FILE* in);
struct header read_header(FILE* in);
struct bmp_header set_header(uint64_t width, uint64_t height);
enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image* img );