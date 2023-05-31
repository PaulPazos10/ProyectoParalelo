#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PNG.h"

PNG* read_image(char* path){
    FILE* pngimage = fopen(path,"rb");
    if(pngimage == NULL){
        printf("Error al abrir imagen PNG \n");
        return 1;
    }

    PNG* p = (PNG*)malloc(sizeof(PNG));
    p->width = 1554;
    p->height = 859;
    p->depth = 3;
    Pixel** imagematrix = (Pixel**)malloc(p->height * sizeof(Pixel*));
    for(unsigned int i = 0;i < p->height; i++){
        imagematrix[i] = (Pixel*)malloc(p->width *sizeof(Pixel));
    }
    for(unsigned int i = 0; i<p->height;i++){
        for(unsigned int j = 0; j<p->width;j++){
            Pixel pixel;
            fread(&pixel,sizeof(pixel),1,pngimage);
            imagematrix[i][j] = pixel;
        }
    }
    p->pixels = imagematrix;
    //unsigned int x = 20;
    //unsigned int y = 10;

    /*printf("PIXEL (%u,%u): R= %u, G=%u, B=%u\n",x,y,p->pixels[y][x].r,p->pixels[y][x].g,p->pixels[y][x].b);
    if (p->pixels  == NULL ){
        printf("Error cargar memoria\n");
        fclose(pngimage);
        return 1;
    }*/

    fclose(pngimage);
    return p;
}

void write_image(PNG *p, char* path_out){
    FILE * pngoutimage = fopen(path_out,"wb");
    if(!pngoutimage){
        printf("Error al abrir el archivo PNG para escritura");
        fclose(pngoutimage);
        return 1;
    }
    // PNG Signature
    unsigned char pngSignature[] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
    //fwrite(pngSignature, 1, sizeof(pngSignature), pngoutimage);

    // IHDR Chunk
    unsigned int ihdrLength = 13;
    unsigned char ihdrType[] = { 'I', 'H', 'D', 'R' };
    unsigned char ihdrData[13];
    unsigned int imageWidth = p->width;
    unsigned int imageHeight = p->height;
    // Set the image width and height
    ihdrData[0] = (imageWidth >> 24) & 0xFF;
    ihdrData[1] = (imageWidth >> 16) & 0xFF;
    ihdrData[2] = (imageWidth >> 8) & 0xFF;
    ihdrData[3] = imageWidth & 0xFF;
    ihdrData[4] = (imageHeight >> 24) & 0xFF;
    ihdrData[5] = (imageHeight >> 16) & 0xFF;
    ihdrData[6] = (imageHeight >> 8) & 0xFF;
    ihdrData[7] = imageHeight & 0xFF;
    // Set the bit depth, color type, and compression method
    ihdrData[8] = 8;  // Bit depth: 8 bits per channel
    ihdrData[9] = 2;  // Color type: RGB
    ihdrData[10] = 0; // Compression method: Deflate/Inflate with a sliding window of at most 32768 bytes
    // Set the filter method and interlace method
    ihdrData[11] = 0; // Filter method: Adaptive filtering with five basic filter types
    ihdrData[12] = 0; // Interlace method: No interlace
    // Write the IHDR chunk
    //fwrite(&ihdrLength, sizeof(ihdrLength), 1, pngoutimage);
    //fwrite(ihdrType, sizeof(ihdrType), 1, pngoutimage);
    //fwrite(ihdrData, sizeof(ihdrData), 1, pngoutimage);

    // IDAT Chunk (Image Data)
    unsigned int idatLength = imageWidth * imageHeight * 3; // Assuming 8 bits per channel (RGB)
    unsigned char idatType[] = { 'I', 'D', 'A', 'T' };
    // Flatten the pixel matrix into a linear array
    unsigned char* pixelData = (unsigned char*)malloc(idatLength);
    unsigned int index = 0;
    for (unsigned int i = 0; i < imageHeight; i++) {
        for (unsigned int j = 0; j < imageWidth; j++) {
            pixelData[index++] = p->pixels[i][j].r;
            pixelData[index++] = p->pixels[i][j].g;
            pixelData[index++] = p->pixels[i][j].b;
        }
    }
    // Write the IDAT chunk
    //fwrite(&idatLength, sizeof(idatLength), 1, pngoutimage);
    //fwrite(idatType, sizeof(idatType), 1, pngoutimage);
    fwrite(pixelData, idatLength, 1, pngoutimage);
    free(pixelData);

    // IEND Chunk
    unsigned int iendLength = 0;
    unsigned char iendType[] = { 'I', 'E', 'N', 'D' };
    // Write the IEND chunk
    //fwrite(&iendLength, sizeof(iendLength), 1, pngoutimage);
    //fwrite(iendType, sizeof(iendType), 1, pngoutimage);

    fclose(pngoutimage);
    return 1;
}
