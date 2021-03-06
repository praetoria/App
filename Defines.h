#ifndef DEFINESH
#define DEFINESH
#ifdef _WIN32
#define nullptr NULL
#endif

#define DEFAULT_TEXT_SIZE 25
#define DEFAULT_BUTTON_SIZE 30
#define DEFAULT_INPUT_WIDTH 20

#define SCREENW 400
#define SCREENH 500

extern char _binary_background_bmp_start;
extern char _binary_background_bmp_end;
#define BG_START (void*) &_binary_background_bmp_start
#define BG_SIZE \
((size_t) (&_binary_background_bmp_end - &_binary_background_bmp_start))

#define WINFONT "C:\\Windows\\fonts\\Arial.ttf"
// #define LINFONT "/usr/share/fonts/TTF/DejaVuSansMono.ttf"
#define LINFONT "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono.ttf"
#endif
