#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int i, first = 0, second = 1, next, count = 0;
    
    for (i = 0; next < 4000000; i++)
    {
        next = first + second;
        first = second;
        second = next;
        //printf ("%d\n", next);
        if (second % 2 == 0) 
        {
            count += next; 
        }
    }
    printf ("%d\n", count);
}
