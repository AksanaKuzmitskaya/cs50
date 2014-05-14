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
    if (argc != 2) 
    {
        printf("Usage: ./asciimath key\n");
        return 1;
    }
    else 
    {
        int key = atoi(argv[1]); 
        string text = GetString();
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            char letter = text[i];
            int result; 
            if (isupper(letter))
            {
                result = ((letter - 65) + key) % 26 + 65;
            }   
            else if (islower(letter))
            {
                result = ((letter - 97) + key) % 26 + 97;
            }
            else
            {
                result = letter;
            }
            printf("%c", result);
         }   
         printf("\n");
    }
}
