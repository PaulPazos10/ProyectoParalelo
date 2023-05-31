#include "png.h"

png::png(
         )
{
    this->width = width;
    this->height = height;
    this->depth = depth;
}

png::~png()
{
    //dtor
}

int png::get_width(){
    return this->width;
}
int png::get_height(){
    return this->height;
}
int png::get_depth(){
    return this->depth;
}
