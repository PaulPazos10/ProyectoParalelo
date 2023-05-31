#ifndef PNG_H
#define PNG_H
#include <stdint.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct{
    int width;
    int height;
    int depth;
    Pixel** pixels;
} PNG;



PNG* read_image(char* path);
void write_image(PNG *p, char* path_out);

#endif // PNG_H


