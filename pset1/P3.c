#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int f = 13196;
    for (int i = 13195; i > 1; i--)
    {
        f /=i;
    }
    printf ("%d\n", f);
}
