/**
 * appends.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Write a function that appends a new node containing int i at the end of a singly linked list
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    // the value to store in this node
    int n;

    // the link to the next node in the list
    struct node* next;
}
node;

node* head = NULL;

void append(int i)
{ 
    // build new node
    node* new_node = malloc(sizeof(node));
    
    if (new_node == NULL)
    {
        exit(1);
    }
    
    // initialize new node
    new_node->n = i;
    
    // if the list is empty, prepend
    if (head == NULL)
    {
        new_node->next = head;
        head = new_node;    
    }
    else
    {
        // traverse list with two pointers
        node* curr = head; 
        node* prev = NULL;
        while(curr != NULL)
        {
            prev = curr;
            curr = curr->next;
        }
    
        // add new node to end of list
        new_node->next = curr;
        prev->next = new_node;  
    }    
}

int main(int argc, char* argv[])
{
    // creating list
    printf("Appending ints 0-%i onto the list...\n", SIZE - 1);
    for (int i = 0; i < SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");

    // printing out list
    printf("Your list contains ");
    for (node*  ptr = head; ptr != NULL; ptr = ptr->next)
    {
        printf("%i ", ptr->n);
    }
    printf("\n");

    return 0;
}
