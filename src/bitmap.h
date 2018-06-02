#ifndef _bitmap_h
#define _bitmap_h

#include "vect.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void bmpSaveImage(Vect **image, int width, int height, const char *fileName);
static void createFileHeader(int width, int height, unsigned char* fileHeader);
static void createInfoHeader(int width, int height, unsigned char* infoHeader);

#endif
