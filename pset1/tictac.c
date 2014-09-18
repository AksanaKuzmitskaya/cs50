#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int x;
    int y = 0;
    for (x = 1; x < 1000; x++)
    {
        if (x % 3 == 0 || x % 5 == 0)
        {
            y +=x;
        } 
    }
    printf ("%d\n", y);
}
