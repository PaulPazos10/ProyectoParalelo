#include <stdio.h>
#include <stdlib.h>

#include "png.h"
int main()
{
    char* path = "C:/Users/LENOVO/Desktop/casa.png";
    PNG* p = read_image(path);
    printf("Ancho:  %d\n", p->width);
    printf("Altp:  %d\n", p->height);
    printf("Prof:  %d\n", p->depth);
    char* path_out = "C:/Users/LENOVO/Desktop/casa_new.png";
    write_image(p,path_out);
    return 0;
}
