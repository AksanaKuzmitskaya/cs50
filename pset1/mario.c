/**
 * mario.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Says hello to the world.
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
    
    int i;
    for (i = 0; i < n; i++)
    {
        int m;
        for (m = n-i-1; m > 0; m--)       
        {
            printf(" ");            
        }
        int k;
        for (k = 0; k < i+2; k++)       
        {
            printf("#");            
        }
        printf("\n");
    }
}
