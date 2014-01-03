// Skye Croke <scroke@asu.edu>, Ashish Datta <adatta4@asu.edu>
//



#include "Bmp.h"

#ifndef IMAGE_H
#define IMAGE_H

void flipv(tPixel **, int32_t, int32_t);
void fliph(tPixel **, int32_t, int32_t);
tPixel **rotr(tPixel **, uint8_t, tBmpInfoHeader *);
tPixel **rotate90(tPixel **, tBmpInfoHeader *);

#endif
