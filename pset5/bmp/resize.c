/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 * Resizes 24-bit uncompressed BMPs by a factor of n. 
 * Accepts exactly three command-line arguments, per the below usage, 
 * whereby the first (n) is a positive integer less than or equal to 100, 
 * the second the name of the file to be resized, 
 * and the third the name of the resized version to be written.
 *
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    // remember factor n
    int n = atoi(argv[1]);
    
    // ensure proper n
    if (n > 100 || n < 0)
    {
        printf("n must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }
    
    // determine padding for infile's scanlines
    int paddingIn =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // store infile's width and height    
    int width = bi.biWidth;
    int height = bi.biHeight;
    
    // determine outfile's width and height
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding for outfile's scanlines
    int paddingOut =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine outfile's size and image size.
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingOut) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
    
        // save the current position of input file pointer
        long positionIn = ftell(inptr);
        
        for (int k = 0; k < n; k++)
        {
        
            // retrieve the position of input pointer to copy it 'n' times    
            fseek(inptr, positionIn, SEEK_SET);
            
            // iterate over pixels in scanline
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);  
                    
                for (int m = 0; m < n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
       

            // skip over padding, if any
            fseek(inptr, paddingIn, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
