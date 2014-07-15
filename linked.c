/**
 * linked.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * week 7 section
 * 
 *
 * practice using linked lists
 */

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// typedef a node for the linked list
typedef struct node
{
    int n;
    struct node* next;
}
node;

// function prototypes
bool insert_node(int value);
void print_nodes(node* list);
void free_nodes(node* list);

// global variable for the head of the list
node* head = NULL;

int main(void)
{
    // offer the user two options
    while (true)
    {
        printf("Please choose an option (0, 1, 2): ");
        int option = GetInt();
        
        switch (option)
        {
            // quit
            case 0:
                free_nodes(head);
                printf("Goodbye!\n");
                return 0;
            
            // insert int into linked list
            case 1:
                printf("Please enter an int: ");
                int v = GetInt();
                char* success = insert_node(v) ? "was" : "was not";
                printf("The insert %s successful.\n", success);
                break;
            
            // print all ints
            case 2:
                print_nodes(head);
                break;
            
            default:
                printf("Not a valid option.\n");
                break;
        }
    }
}

/**
 * Create a new node for a given value and insert it into a list.
 */
bool insert_node(int value)
{
    // create a new node
    node* new_node = malloc(sizeof(node));
    
    if (new_node == NULL)
    {
        printf("Out of a heap memory\n");
        return false;
    }
    
    new_node->n = value;
    
    // first insertion
    if (head == NULL)
    {
        new_node->next = head;
        head = new_node;
        return true;
    }
    
    // create curr and prev pointers
    node* curr = head;
    node* prev = NULL; 
    
    // go through the list
    while (curr != NULL)
    {
        // don't insert duplicates
        if (curr->n == value)
        {
            free(new_node);
            return false;
        }
        
        // if value > this node
        else if (value > curr->n)
        {       
            // insert before
            prev = curr;
            curr = curr->next;
            
            // if the end of the list
            if (curr == NULL)
            {
                break;
            } 
        } 
           
        // if value < this node
        else if (value < curr->n)
        {
            break;
        }
    }
                
    // insert value into correct position            
    new_node->next = curr;
    if (prev == NULL)
    {
        head = new_node;
    }
    else
    {
        prev->next = new_node;
    }
    return true;
}

/**
 * Print out all of the ints in a list.
 */
void print_nodes(node* list)
{
    // save a counter
    int count = 0;
    
    node* new_node = head;    
    
    // print all of the ints in a list
    while (new_node != NULL)
    {
        count++;
        printf("%d: %d \n", count, new_node->n);
        new_node = new_node->next;
    }
}

/**
 * Frees all of the nodes in a list upon exiting the program.
 */
void free_nodes(node* list)
{   
    //don't lose the rest of the list
    node* curr = head;
    node* prev = NULL;    
    
    // free all of the nodes in a list
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
}
