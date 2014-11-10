#ifndef DEFINESH
#define DEFINESH
#define DEFAULT_TEXT_SIZE 25
#define DEFAULT_BUTTON_SIZE 30
#define SCREEN_W 640
#define SCREEN_H 480
extern char _binary_background_bmp_start;
extern char _binary_background_bmp_size;
extern char _binary_background_bmp_end;
#define BG_START (void*) &_binary_background_bmp_start
#define BG_SIZE \
((size_t) (&_binary_background_bmp_end - &_binary_background_bmp_start))
#endif
