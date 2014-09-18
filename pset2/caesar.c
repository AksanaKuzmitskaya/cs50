/**
 * caesar.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Encrypts messages using Caesar’s cipher.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{   
 
    // check whether number of command-line arguments equals 2
    if (argc != 2) 
    {
        printf("Usage: ./asciimath key\n");
        return 1;
    }
    else 
    {
        int key = atoi(argv[1]); 
        
        // get the message from the user
        string text = GetString();
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            char letter = text[i];
            int result;
            
            //capitalized letters, though rotated, remain capitalized letters 
            if (isupper(letter))
            {
                result = ((letter - 65) + key) % 26 + 65;
            } 
            
            //lowercase letters, though rotated, remain lowercase letters
            else if (islower(letter))
            {
                result = ((letter - 97) + key) % 26 + 97;
            }
            
            // if the character in text is not a letter, output this character unchanged
            else
            {
                result = letter;
            }
            printf("%c", result);
         }   
         printf("\n");
    }
}





