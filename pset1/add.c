#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    printf("Please give me a string: ");
    string s = GetString();
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c\n", s[i]);
    }
}
