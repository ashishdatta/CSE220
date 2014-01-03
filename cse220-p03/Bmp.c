//Skye Croke <scroke@asu.edu>, Ashish Datta <adatta4@asu.edu>
//


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "Bmp.h"
#include "Error.h"
#include "Image.h"

const size_t cSizeofBmpHeader = 14;
const size_t cSizeofBmpInfoHeader = 40;
const size_t cSizeofPixel = 3;

tPixel** readBitmap(char *fileName, tBmpHeader *bmpHeader, tBmpInfoHeader *bmpInfoHeader)
{	
	// read in the filesize using stat
	struct stat fileStat;
	if(stat(fileName, &fileStat) != 0)
		ErrorExit(cErrorFileOpen,"could not open %s",fileName);

	long fileSize = (long)fileStat.st_size;
	
	// check that filesize is at least 58 bytes
	if(fileSize < 58)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (file size too small)",fileName);

	// read in file
	FILE *bmpIn = fopen(fileName,"rb"); 
	if (bmpIn == NULL) 
		ErrorExit(cErrorFileOpen,"%s could not be opened for reading",fileName);
	
	// read in the BITMAPFILEHEADER
	byte buffer[sizeof(tBmpHeader)];
	if (fread(buffer, cSizeofBmpHeader, 1, bmpIn) != 1)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (unable to read BITMAPFILEHEADER)",fileName);

	//Copy signature bytes from buffer to structure.
	bmpHeader->signature_B = buffer[0];
	bmpHeader->signature_M = buffer[1];

	//Copy fileSize bytes from buffer to structure.
	memcpy(&bmpHeader->fileSize, &buffer[2], sizeof(bmpHeader->fileSize));

	//Copy reserved1 and reserved2 bytes from buffer to structure.
	memcpy(&bmpHeader->reserved1, &buffer[6], sizeof(bmpHeader->reserved1));
	memcpy(&bmpHeader->reserved2, &buffer[8], sizeof(bmpHeader->reserved2));

	//Copy pixelOffset bytes from buffer to structure.
	memcpy(&bmpHeader->pixelOffset, &buffer[10], sizeof(bmpHeader->pixelOffset));

	// read in the BITMAPINFOHEADER
	byte infoBuffer[sizeof(tBmpInfoHeader)];
	if (fread(infoBuffer, cSizeofBmpInfoHeader, 1, bmpIn) != 1)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (unable to read BITMAPINFOHEADER)",fileName);

	//Copy sizeBmpHeader bytes from infoBuffer to structure.
	memcpy(&bmpInfoHeader->sizeBmpHeader, &infoBuffer[0], sizeof(bmpInfoHeader->sizeBmpHeader));

	//Copy width & height bytes from infoBuffer to structure.
	memcpy(&bmpInfoHeader->width, &infoBuffer[4], sizeof(bmpInfoHeader->width));
	memcpy(&bmpInfoHeader->height, &infoBuffer[8], sizeof(bmpInfoHeader->height));

	//Copy bitPlanes & bitsPerPixel bytes from infoBuffer to structure.
	memcpy(&bmpInfoHeader->bitPlanes, &infoBuffer[12], sizeof(bmpInfoHeader->bitPlanes));
	memcpy(&bmpInfoHeader->bitsPerPixel, &infoBuffer[14], sizeof(bmpInfoHeader->bitsPerPixel));
	
	//Copy zeros bytes from infoBuffer to structure.
	memcpy(&bmpInfoHeader->zeros, &infoBuffer[16], 24);

	// test signature == 'BM'
	if(bmpHeader->signature_B != 'B' || bmpHeader->signature_M != 'M')
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid signature)",fileName);

	// check that header filesize equals actual filesize
	if(bmpHeader->fileSize != fileSize)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (header filesize not equal to actual filesize)",fileName);

	// test that reserved1 and reserved2 are zero
	if(bmpHeader->reserved1 != 0)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid value for reserved1)",fileName);
	if(bmpHeader->reserved2 != 0)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid value for reserved2)",fileName);

	// test that pixelOffset = 0x36
	if(bmpHeader->pixelOffset != 0x36)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid pixel offset)",fileName);

	// test that sizeBmpHeader = 0x28
	if(bmpInfoHeader->sizeBmpHeader != 0x28)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid size of BITMAPINFOHEADER)",fileName);

	// test that bitPlanes = 1
	if(bmpInfoHeader->bitPlanes != 1)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid number of color planes)",fileName);

	// test that bitsPerPixel = 0x18
	if(bmpInfoHeader->bitsPerPixel != 0x18)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (invalid bits per pixel)",fileName);

	// calculate padding
	byte pad = (4-(3 * bmpInfoHeader->width) % 4) %4;

	// make sure calcuated filesize based on width, height and padding = actual filesize
	if((bmpInfoHeader->height * (3 * bmpInfoHeader->width + pad) + 54) != fileSize)
		ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (calculated filesize is not equal to actual file size)",fileName);

	// create memory for 2D array of pixels 
	tPixel **pixels = (tPixel **)malloc(bmpInfoHeader->height * sizeof(tPixel *));
	for (int row = 0; row < bmpInfoHeader->height; ++row) 
	{
		pixels[row] = (tPixel *)malloc(bmpInfoHeader->width * sizeof(tPixel));
	}	

	byte padByte;  // a byte variable for testing padding bytes

	//	loop through all of the rows in the bitmap (0..height)
	for (int row = 0; row < bmpInfoHeader->height; ++row)
	{
		//	loop through all of the columns in each row (0..width)
		for ( int col = 0; col < bmpInfoHeader->width; ++col) {
			// read in the pixel
			if (fread(&pixels[row][col], cSizeofPixel, 1, bmpIn) != 1)
			{ 
				ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (Unable to read pixel data for row %d and column %d)",fileName, row, col);
			}	
		}
		// we might have padding bytes at the end of each row
		for ( int p = 0; p < pad; p++ ) {
			// read in each paddin byte
			if ( fread(&padByte, 1, 1, bmpIn) != 1) {
				ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (Unable to read padding byte for row %d and padding byte %d)",fileName, row, p);
			} else {
				// check to make sure the padding byte is zero
				if (padByte != 0) {
					ErrorExit(cErrorFileOpenRead,"%s is not a valid BMP or or is corrupted (Padding byte for row %d and padding byte %d is not zero)",fileName, row, p);
				}	
			}
		}
	}
	return pixels;
}

void writeBitmap(char *fileName, tBmpHeader *bmpHeader, tBmpInfoHeader *bmpInfoHeader, tPixel **pixels) 
{
	// open the file for writing in binary
	FILE *bmpOut = fopen(fileName, "wb"); 
	if (bmpOut == NULL) 
		ErrorExit(cErrorFileOpen, "could not open %s" , fileName);

	// buffer for BmpHeader
	byte buffer[sizeof(tBmpHeader)];

	// Copy data from bmpHeader to buffer
	buffer[0] = bmpHeader->signature_B;
	buffer[1] = bmpHeader->signature_M;

	// calculate padding
	byte pad = (4-(3 * bmpInfoHeader->width) % 4) %4;
	byte padByte = 0;  // a byte variable for testing padding bytes

	// calculate fileSize
	int32_t fileSize = 54; // size of headers
	fileSize += bmpInfoHeader->width * bmpInfoHeader->height * sizeof(tPixel);
	fileSize += bmpInfoHeader->height * pad;
	bmpHeader->fileSize = fileSize;
	memcpy(&buffer[2],&bmpHeader->fileSize, sizeof(bmpHeader->fileSize));

	//Copy reserved1 and reserved2 bytes from buffer to structure.
	memcpy(&buffer[6],&bmpHeader->reserved1, sizeof(bmpHeader->reserved1));
	memcpy(&buffer[8],&bmpHeader->reserved2, sizeof(bmpHeader->reserved2));

	//Copy pixelOffset bytes from buffer to structure.
	memcpy(&buffer[10],&bmpHeader->pixelOffset, sizeof(bmpHeader->pixelOffset));

	// array for bmpInfoHeader
	byte infoBuffer[sizeof(tBmpInfoHeader)];

	//Copy sizeBmpHeader bytes from infoBuffer to structure.
	memcpy(&infoBuffer[0], &bmpInfoHeader->sizeBmpHeader, sizeof(bmpInfoHeader->sizeBmpHeader));

	//Copy width & height bytes from infoBuffer to structure.
	memcpy(&infoBuffer[4], &bmpInfoHeader->width, sizeof(bmpInfoHeader->width));
	memcpy(&infoBuffer[8], &bmpInfoHeader->height, sizeof(bmpInfoHeader->height));

	//Copy bitPlanes & bitsPerPixel bytes from infoBuffer to structure.
	memcpy(&infoBuffer[12], &bmpInfoHeader->bitPlanes, sizeof(bmpInfoHeader->bitPlanes));
	memcpy(&infoBuffer[14], &bmpInfoHeader->bitsPerPixel, sizeof(bmpInfoHeader->bitsPerPixel));
	
	//Copy zeros bytes from infoBuffer to structure.
	memcpy(&infoBuffer[16],&bmpInfoHeader->zeros, 24);

	// write bmpHeader
	if (fwrite(buffer, cSizeofBmpHeader, 1, bmpOut) != 1)
		ErrorExit(cErrorFileOpen, "could not write header to %s. ", fileName);

	// write bmpInfoHeader
	if (fwrite(infoBuffer, cSizeofBmpInfoHeader, 1, bmpOut) != 1)
		ErrorExit(cErrorFileOpen, "could not write info header to %s. ", fileName);

	//	loop through all of the rows in the bitmap (0..height)
	for (int row = 0; row < bmpInfoHeader->height; ++row)
	{
		//	loop through all of the columns in each row (0..width)
		for ( int col = 0; col < bmpInfoHeader->width; ++col) 
		{
			// write out the pixel
			if (fwrite(&pixels[row][col], cSizeofPixel, 1, bmpOut) != 1) 
			{ 
				ErrorExit(cErrorFileOpen,"Unable to write pixel data for row %d and column %d)",fileName, row, col);
			}	
		}
		// pad bytes at the end of each row
		for ( int p = 0; p < pad; p++ ) 
		{
			// read in each paddin byte
			if ( fwrite(&padByte, 1, 1, bmpOut) != 1) 
			{
				ErrorExit(cErrorFileOpen,"Unable to write padding byte for row %d and padding byte %d)",fileName, row, p);
			}
		}
	}
	// Close file
	fclose(bmpOut);	
}

