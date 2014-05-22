/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 * 
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Helper functions for Problem Set 3.
 * (I have implemented search and sort functions)
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
