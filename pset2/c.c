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
    int key = atoi(argv[1]);
    if (argc != 2 || key == 0) 
    {
        printf("Usage: ./asciimath key\n");
        return 1;
    }
    int letter = 'A';
    printf("\nCalculating: %c + %d...\n", letter, key);
    int result = letter + key;
    printf("The ASCII value of %c is %d\n", result, result);
    
}
