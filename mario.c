/**
 * mario.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Recreates half-pyramid using hashes (#) for blocks. First prompt the user for the half-pyramid’s height, 
 * a non-negative integer no greater than 23.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int n;
    
    do 
    {
        printf("Height: ");
        n = GetInt();   
    }
    while (n > 23 || n < 0);
   
    for (int i = 0; i < n; i++)
    {
        for (int m = n - i - 1; m > 0; m--)       
        {
            printf(" ");            
        }
        for (int k = 0, l = i + 2; k < l; k++)       
        {
            printf("#");            
        }
        printf("\n");
    }
}

