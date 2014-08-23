#include <stdio.h>

#define SIZE 8

void sort(int array[], int size)
{
   
   for(int i = 0, temp = 0; i < (size - 1); i++)
   {
        for(int j = i + 1; j < size; j++)
        {
            if(array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp; 
            }
        }
   }
}

int main(void)
{
    int numbers[SIZE] = {4, 15, 16, 50, 8, 23, 42, 108};
    
    sort(numbers, SIZE);
    
    for(int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
}
