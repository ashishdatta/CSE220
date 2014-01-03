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

void flipv(tPixel **pixels, int32_t width, int32_t height)
{
	// setup temp array
	tPixel **temp = (tPixel **)malloc(height * sizeof(tPixel *));
	for (int row = 0; row < height; ++row) 
	{
		temp[row] = (tPixel *)malloc(width * sizeof(tPixel));
	}	

	// copy pixels into temp
	for (int row = 0; row < height; ++row) 
	{
		for ( int col = 0; col < width; ++col) 
		{
			memcpy(&temp[row][col], &pixels[row][col], sizeof(tPixel));
		}
	}

	// flip
	// col = col
	// row = height - row - 1
	for (int row = 0; row < height; ++row) 
	{
		for ( int col = 0; col < width; ++col) 
		{
			memcpy(&pixels[row][col], &temp[height-row-1][col], sizeof(tPixel));
		}
	}

	// free temp array
	for (int row = 0; row < height; row++) free(temp[row]);
}

// Pixels passed by reference for faster execution
void fliph(tPixel **pixels, int32_t width, int32_t height)
{
	// setup temp array
	tPixel **temp = (tPixel **)malloc(height * sizeof(tPixel *));
	for (int row = 0; row < height; ++row) 
	{
		temp[row] = (tPixel *)malloc(width * sizeof(tPixel));
	}	

	// copy pixels into temp
	for (int row = 0; row < height; ++row) 
	{
		for ( int col = 0; col < width; ++col) 
		{
			memcpy(&temp[row][col], &pixels[row][col], sizeof(tPixel));
		}
	}

	// flip
	// row = row
	// col = width - col - 1
	for (int row = 0; row < height; ++row) 
	{
		for ( int col = 0; col < width; ++col) 
		
		{
			memcpy(&pixels[row][col], &temp[row][width-col-1], sizeof(tPixel));
		}
	}

	// free temp array
	for (int row = 0; row < height; row++) free(temp[row]);
}

// pixels are returned instead of passed by reference for less code
// and trying another way to do this
tPixel **rotr(tPixel **pixels, uint8_t n, tBmpInfoHeader *bmpInfoHeader) 
{
	// variable for rotated array of pixels
	tPixel **rotated;

	// if n % 4 == 0, nothing to do 
	if ( n % 4 == 0 ) 
	{
		return pixels;
	}

	// rotate 90 degrees for each n%4
	for (int i=0; i < n % 4; i++) 
	{
		if ( i == 0 ) 
		{
			rotated = rotate90(pixels, bmpInfoHeader);
		} 
		else
		{
			rotated = rotate90(rotated, bmpInfoHeader);
		}
	}

	return rotated;
}

// function to rotate 90 degrees
// like rotr, pixels are passed by value and a new array is returned
tPixel **rotate90(tPixel **pixels, tBmpInfoHeader *bmpInfoHeader)
{
	// local variables to hold width & height since we'll be changing them
	int32_t width = bmpInfoHeader->width;
	int32_t height = bmpInfoHeader->height;

	// setup temp array
	// swapping rows and columns
	tPixel **temp = (tPixel **)malloc(width * sizeof(tPixel *));
	for (int row = 0; row < width; ++row) 
	{
		temp[row] = (tPixel *)malloc(height * sizeof(tPixel));
	}	

	// copy pixels into temp
	for (int row = 0; row < height; ++row)
	{
		for ( int col = 0; col < width; ++col) 
		{
			memcpy(&temp[col][row], &pixels[row][col], sizeof(tPixel));
		}
	}

	// to complete the rotation, we need to flip vertical
	flipv(temp, height, width);

	// swap width and height in bmpInfoHeader
	bmpInfoHeader->width = height;
	bmpInfoHeader->height = width;

	// free original pixels array
	for (int row = 0; row < height; row++) free(pixels[row]);

	return temp;
}
