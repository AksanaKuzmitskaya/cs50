#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    int n;
    struct node* next;
}
node;

node* head = NULL;

int length(void)
{
    int count = 0;
    if (head == NULL)
    {
        return 0;
    }
    node* new = malloc(sizeof(node));
    new = head;
    while (new != NULL)
    {
        new = new->next;
        count++;
    }
    return count;
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < SIZE; i++)
    {
        node* new = malloc(sizeof(node));
        
        if (new == NULL)
        {
            exit(1);
        }
        new->n = i;
        new->next = head;
        head = new;        
    }
    printf("Making sure that list length is indeed %i...\n", SIZE);
    assert(length() == SIZE);
    printf("good!\n");
    return 0;
}
