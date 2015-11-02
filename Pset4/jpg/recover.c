/**
 * Benjamin Burgess
 *
 * anathemus@gmail.com
 *
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    // the block size to read/write is 512 bytes.
    int block_size = 512;
    
    
    // in and out pointers    
    FILE *ifn, *ofn;
    
    // opens the memory card image to be read
    ifn = fopen("card.raw", "r");
    if (ifn == NULL)
    {
        printf("File does not exist.");
        return 1;
    }
        
    BYTE buffer[512];
    
    char filename[8];
    int n = 0;
    int open = 0;
    
    while (fread(buffer, block_size, 1, ifn) > 0)
    {
        // int *header = buffer;
        
         if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // closes the file at the recognized jpeg signature
            if (open == 1)
            {
                fclose(ofn);
                open = 0;
            }
            if (open == 0)
            {
                sprintf(filename, "%03d.jpg", n++);
                ofn = fopen(filename, "w");
                open = 1;
            }
            
            // error check. Shouldn't be NULL
            if (ofn == NULL)
            {
                printf("File could not be created.");
                return 1;
            }
                        
        }
        // write the file
        if (open == 1)
            {
                fwrite(buffer, block_size, 1, ofn);
            }
        
    }
    
    fclose(ofn);  
    fclose(ifn);
    return 0;
}
