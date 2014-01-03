//Skye Croke <scroke@asu.edu>, Ashish Datta <adatta4@asu.edu>
//


#include <stdint.h>

#ifndef BMP_H
#define BMP_H

typedef uint8_t byte;

typedef struct 
{
	byte 		signature_B;
	byte 		signature_M;
	int32_t		fileSize;
	int16_t 	reserved1;
	int16_t		reserved2;
	int32_t		pixelOffset;
} tBmpHeader;

typedef struct 
{
	int32_t		sizeBmpHeader;
	int32_t		width;
	int32_t		height;
	int16_t		bitPlanes;
	int16_t		bitsPerPixel;
	byte		zeros[24];

} tBmpInfoHeader;

typedef struct
{
	byte blue;
	byte green;
	byte red;
} tPixel;

tPixel **readBitmap(char *, tBmpHeader *, tBmpInfoHeader *);
void writeBitmap(char *, tBmpHeader *, tBmpInfoHeader *, tPixel **);

#endif
