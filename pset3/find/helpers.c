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
    int min = 0, max = n - 1, midpoint;
    while ((max - min + 1) > 0)
    {
        midpoint = (max - min + 1)/ 2 + min;
        if (values[midpoint] == value)
        {
            return true;
        }
        else if (values[midpoint] < value)
        {       
            min = midpoint + 1;
        }
        else if (values[midpoint] > value)
        {
            max = midpoint - 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // an O(n^2) sorting algorithm
    for (int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1, min; j < n; j++)
        {
            if (values[i] > values[j])
            {
                min = values[j];
                values[j] = values[i];
            }
            else 
            {
                min = values[i];
            } 
            values[i] = min;
        } 
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", values[i]);
    }
}
