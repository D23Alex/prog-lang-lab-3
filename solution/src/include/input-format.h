#include <stdint-gcc.h>

enum open_status open_bmp(FILE* file);
enum close_status close_bmp(FILE* in);
struct header read_header(FILE* in);
struct bmp_header set_header(uint64_t width, uint64_t height);
enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image* img );