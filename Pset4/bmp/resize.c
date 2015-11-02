/**
 * resize.c
 *
 * Benjamin Burgess
 *
 * anathemus@gmail.com
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // the size to resize, using resize.
    int resize = atoi(argv[1]);
    /* if (resize <= 1)
    * {
    *    return 0;
    * } 
    */

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // storing info in another variable to allow for changes
    BITMAPFILEHEADER new_bf;
    BITMAPINFOHEADER new_bi;	
	new_bf = bf;
	new_bi = bi;
	new_bi.biWidth = bi.biWidth * resize;
	new_bi.biHeight = bi.biHeight * resize;

	// padding!
	int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int new_padding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // thanks to http://forums.codeguru.com/showthread.php?248117-BMP-file-format for helping with the calculations.
	new_bf.bfSize = 54 + new_bi.biWidth * abs(new_bi.biHeight) * 3 + abs(new_bi.biHeight) *  new_padding;
	new_bi.biSizeImage = ((((new_bi.biWidth * new_bi.biBitCount) + 31) & ~31) / 8) * abs(new_bi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // int k = 0;    
    // RGBTRIPLE pixels[new_bi.biSizeImage];
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
		{
				// copys lines resize value number of times.
				for(int j = 0; j < resize; j++)
				{
						// iterate over pixels in scanline
						for (int k = 0; k < bi.biWidth; k++)
						{
								// temporary storage
								RGBTRIPLE triple;

								// read RGB triple from infile
								fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

								// write RGB triple to outfile * resize
								for(int l = 0; l < resize; l++) 
								{
										fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
								}
						}

						// skip over padding in infile
						fseek(inptr, padding, SEEK_CUR);

						// then add it to outfile
						for (int k = 0; k < new_padding; k++)
								fputc(0x00, outptr);

						fseek(inptr, -(bi.biWidth * 3 + padding ), SEEK_CUR);

				}
				fseek(inptr, bi.biWidth * 3 + padding, SEEK_CUR);
		}


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
