#include "bitmap.h"

void bmpSaveImage(Vect **image, int width, int height, const char *fileName) {
	// Get headers
	unsigned char fileHeader[FILE_HEADER_SIZE];
	unsigned char infoHeader[INFO_HEADER_SIZE];
	createFileHeader(width, height, fileHeader);
	createInfoHeader(width, height, infoHeader);

	// Padding
	unsigned char padding[3] = { 0, 0, 0 };
	int paddingSize = (4 - (width * 3) % 4) % 4;

	// Write to file
	FILE *f = fopen(fileName, "wb");
	fwrite(fileHeader, 1, FILE_HEADER_SIZE, f);
	fwrite(infoHeader, 1, INFO_HEADER_SIZE, f);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			unsigned char r = round(image[height-y-1][x].x * 255.0);
			unsigned char g = round(image[height-y-1][x].y * 255.0);
			unsigned char b = round(image[height-y-1][x].z * 255.0);
			fwrite(&b, 1, 1, f);
			fwrite(&g, 1, 1, f);
			fwrite(&r, 1, 1, f);

			fwrite(padding, 1, paddingSize, f);
		}
	}
}

static void createFileHeader(int width, int height, unsigned char* fileHeader) {
	int dataOffset = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
	int fileSize = dataOffset + 3*height*width;
	
	memset(fileHeader, 0, FILE_HEADER_SIZE);
	// bfType
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';
	// bfSize
	fileHeader[2] = (fileSize) & 0xFF;
	fileHeader[3] = (fileSize >> 8) & 0xFF;
	fileHeader[4] = (fileSize >> 16) & 0xFF;
	fileHeader[5] = (fileSize >> 24) & 0xFF;
	// bfOffBits
	fileHeader[10] = dataOffset;
}

static void createInfoHeader(int width, int height, unsigned char* infoHeader) {
	memset(infoHeader, 0, INFO_HEADER_SIZE);
	// biSize
	infoHeader[0] = INFO_HEADER_SIZE;
	// biWidth
	infoHeader[4] = (width) & 0xFF;
	infoHeader[5] = (width >> 8) & 0xFF;
	infoHeader[6] = (width >> 16) & 0xFF;
	infoHeader[7] = (width >> 24) & 0xFF;
	// biHeight
	infoHeader[8] = (height) & 0xFF;
	infoHeader[9] = (height >> 8) & 0xFF;
	infoHeader[10] = (height >> 16) & 0xFF;
	infoHeader[11] = (height >> 24) & 0xFF;
	// biPlanes
	infoHeader[12] = 1;
	// biCount
	infoHeader[14] = 24;
}
