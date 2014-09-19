/**
 * recover.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(void)
{
   
    // open memory card file
    FILE* file = fopen("card.raw", "r"); 
    if (file == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    // declare a variable for storing file's data in buffer
    BYTE buffer[512];
   
    // store number of the JPGs  
    int count = 0;
    
    char* title = malloc(sizeof(char));
    
    FILE* img = NULL;
      
    // repeat until end of a card
    while (fread(&buffer, 512 * sizeof(BYTE), 1, file) == 1)
    {
              
        // compare first 4 bytes
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] == 224 || buffer[3] == 225))
        {
            if (count != 0)
            {
                // close JPG's file
                fclose(img);
            }
            
            count++;
            
            // name each ###.jpg, where ### is three-digit decimal number from 000 on up
            sprintf(title, "%.3d.jpg", (count - 1));
            
            // open JPG's file
            img = fopen(title, "w");
            if (img == NULL) 
            {
                printf("could not create jpeg file\n");
                return 2;
            } 
            
            // write buffer's data to JPG
            fwrite(&buffer, 512 * sizeof(BYTE), 1, img);
        }
        else if (count!= 0)
        {
            // write buffer's data to JPG
            fwrite(&buffer, 512 * sizeof(BYTE), 1, img);
        }
    }
    
    // close memory card file
    fclose(file);

    // close JPG's file
    fclose(img);

    // that's all folks
    return 0; 
}
