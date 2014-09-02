/****************************************************************************
 * substring.c
 *
 * Computer Science 50
 * 
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Implement strchr(), a standard function that returns a substring of a C 
 * string that starts with a given character. If the character is not in 
 * the string, it should return NULL
 *
 ***************************************************************************/
#include <stdio.h>
#include <cs50.h>

char* my_strchr(char* str, char c)
{
    while (*str != '\0')
    {
        if (*str == c)
        {
            return str;
        }
        str++;
    }
    return NULL;
}

int main(void)
{
    printf("String: ");
    char* str = GetString();
    printf("Character: ");
    char c = GetChar();
    printf("Looking for substring...\n");
    char* result = my_strchr(str, c); 
    if (result == NULL)
    {
        printf("Couldn't find %c.\n", c);
    }
    else
    {
        printf("Substring: %s \n", result);
    }
}
