#include <stdio.h>

#define SIZE 8

int temp[SIZE] = {0};

void merge (int array[], int start_1, int end_1, int start_2, int end_2)
{
    int index = start_1;
    int size = end_2 - start_1 + 1;
    while (start_1 <= end_1 && start_2 <= end_2)
    {
        if (array[start_1] > array[start_2])
        { 
            temp[index] = array[start_2];
            index++;
            start_2++;
        }
        else if (array[start_1] < array[start_2])
        {
            temp[index] = array[start_1];
            index++;
            start_1++;       
        }
    }
    
    while (start_1 <= end_1)
    {
        temp[index] = array[start_1];
        index++;
        start_1++;
    }
    
    while (start_2 <= end_2)
    {
        temp[index] = array[start_2];
        index++;
        start_2++;
    }
    for (int i = 0; i < size; i++)
    {
        array[i] = temp[i];
    }
       
}

void sort (int array[], int start, int end)
{
    if (end > start)
    {
        int middle = (start + end) / 2;

        // sort left half
        sort(array, start, middle);

        // sort right half
        sort(array, middle + 1, end);

        // merge the two halves
        merge(array, start, middle, middle + 1, end);
    }
}

int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108};
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
    sort(numbers, 0, SIZE - 1);
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}
