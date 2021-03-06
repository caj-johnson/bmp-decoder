#include <stdio.h>
#include "bmp.h"

int main()
{
	int i, j;
	FILE *fIn, *fOut;	
	bmp_file bmp;
	BYTE *newPixels;
	
	fIn = fopen("./img/lena512.bmp", "rb");
	bmp = *read_bmp_file(fIn, &bmp);	
	fclose(fIn);
	
	
	newPixels = (BYTE *)malloc(bmp.scan_size_bytes);
	for (i = 0; i < bmp.px_height; i++)
	{		
		for (j = 0; j < bmp.px_width; j++)
		{	
			int destRowOffset =  (bmp.px_height - 1 - j) * bmp.row_size_bytes;
			unsigned char *destAddress = newPixels + destRowOffset + i;
			unsigned char *srcAddress = bmp.pixels + (bmp.row_size_bytes * i) + j;
			memcpy(destAddress, srcAddress, sizeof(BYTE));
		}
	}	
	bmp.pixels = newPixels;	
	
	fOut = fopen("./img/rotated.bmp", "wb+");	
	write_bmp_file(bmp, fOut);
	fclose(fOut);
	
	free_bmp_file(bmp);
	free(newPixels);
	
	return 0;
}