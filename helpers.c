/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    else
    {
    
    // searching algorithm
        int count = 0;
        for (int i = 0; i < n; i++)
        {   
            if (value == values[i])
            {
                count++;
            }
        }
        if (count > 0)
        {
            return true;
        }
        else return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // an O(n^2) sorting algorithm - selection sort
    for (int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1, min, max; j < n; j++)
        {
            if (values[i] > values[j])
            {
                min = values[j];
                max = values[i];
            }
            else 
            {
                min = values[i];
                max = values[j];
            } 
            values[i] = min;
            values[j] = max;
        } 
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", values[i]);
    }
}
