/**
 * greedy.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Asks the user how much change is owed and then spits out the minimum number of coins with which said change can be made. 
 */
 
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change; int amount;
    
    do 
    {
        printf("O hai! How much change is owed?\n");
        change = GetFloat();
        amount = round(change * 100);
    }
    while (change <= 0);
    
    int count = 0; int quarter = 25; int dime = 10; int nickel = 5; 
    
    while (amount % quarter != amount)
    {
        amount -= quarter;
        count++;
    }
    
    while (amount % dime != amount)
    {
        amount -= dime;
        count++;
    }
    
    while (amount % nickel != amount)
    {
        amount -= nickel;
        count++;
    }
    
    count += amount; 
    
    printf ("%d\n", count);
}
