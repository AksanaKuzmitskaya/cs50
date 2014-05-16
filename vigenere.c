/**
 * vigenere.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Encrypts messages using Vigenère’s cipher.
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
        printf("Usage: ./vigenere <keyword> key\n");
        return 1;
    }
    int m = strlen(argv[1]);
    for (int i = 0; i < m; i++)
    {   
        if (isalpha( argv[1][i]) == false)
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        }
    }   
    string text = GetString();
    for (int i = 0, j = 0, result = 0, n = strlen(text); i < n; i++)
    {
        char letter = text[i];
        char key = argv[1][(j) % m];   
        if (isupper(key)) 
        {
           key -= 65; 
        }
        else if (islower(key))
        {
           key -= 97;
        }
        if (isupper(letter))
        {
            result = (letter + key - 65) % 26 + 65;
            j++;
        }   
        else if (islower(letter))
        {
           result = (letter  + key - 97) % 26 + 97;
           j++;
        }
        else
        {
           result = letter;
        }
           printf("%c", result);
    }   
    printf("\n");      
}        
