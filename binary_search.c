#include <cs50.h>
#include <stdio.h>

#define SIZE 8

bool search(int needle, int haystack[], int size)
{
    int min = 0, max = size;
    while (min <= max)
    {
        int middle = (min + max) / 2;
        if(haystack[middle] == needle)
        {
            return true;
        }
        else if(haystack[middle] > needle)
        {
            max = middle - 1;
        }
        else 
        {
            min = middle + 1;
        } 
    }
    return false; 
}

int main(void)
{
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE))
    {
        printf("YES\n");
    }   
    else 
    {
        printf("NO\n");
    }
}
