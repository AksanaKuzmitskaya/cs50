/*H******************************************************
*
...  This code sorts the random values and prints them in sorted order. 
...  The random values depend from user input. 
*
*H*/

#include <stdio.h>
#define MAX 10

int a[MAX];
int rand_seed;

void get_input()
{
    printf("Enter a number: ");
    scanf("%d", &rand_seed);
}

/* from K&R
   - returns random number between 0 and 32767.*/
int rand ()
{
    rand_seed = rand_seed * 1103515245 + 12345;
    return (unsigned int)(rand_seed / 65536) % 32768;
}

/* bubble sort the array */
void bubble_sort()
{
    int t, x, y;
    for (x = 0; x < MAX - 1; x++)
        for (y = 0; y < MAX - x - 1; y++)
            if (a[y] > a[y + 1])
            {
                t = a[y];
                a[y] = a[y + 1];
                a[y + 1] = t;
            }
}

int main()
{   
    get_input();
    int i;
    
    /* fill array */
    for (i = 0; i < MAX; i++)
    {
        printf("%d\n", a[i] = rand());
    }
    
    bubble_sort();
    
    /* print sorted array */
    printf("----------------------\n");
    for (i = 0; i < MAX; i++)
    printf("%d\n", a[i]);
    return 0;
}
