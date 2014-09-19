/****************************************************************************
 * dictionary.c
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// typedef a node for the linked lists
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

int HASH_SIZE = 179479;

// store size of dictionary
int lines = 0;

node* hashtable[179479];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int len = strlen(word);
    
    // store word with converted letters to lowercase 
    char* lower_word = malloc(sizeof(char)*(len+1));
    if (lower_word == NULL)
    {
        printf("Out of a heap memory\n");
        return false;
    }
    
    // convert letter to lowercase
    for (int i = 0; i < len; i++)
    {
        if (isupper(word[i]))
        {  
            lower_word[i] = tolower(word[i]);
        }
        else
        {
            lower_word[i] = word[i];
        }
    }
    lower_word[len] = '\0';
    
    // hash that word
    long key = hash(lower_word);   
    node* new = hashtable[key];
    
    // check if word is in dictionary
    while (new != NULL)
    { 
        if (strcmp (new->word, lower_word) == 0)
        {
            free(lower_word);
            return true;
        }
        else
        {
            new = new->next;
        }
    }
    free(lower_word);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    
    int ch;
    
    // count words in dictionary
    while ((ch = fgetc(dic)) != EOF)
    {
        if(ch == '\n')
        {
            lines++;
            ch = '\0';
        }
    }
    
    // set the file position of the stream to the beginning of file
    fseek( dic, 0, SEEK_SET );
      
    while (1)
    {
        // malloc a *node for each new word
        node* new_node = malloc(sizeof(node));
        
        if (new_node == NULL)
        {
            printf("Out of a heap memory\n");
            return false;
        } 
    
        // scan a string from our dictionary file into new_node->word (destionation of that word)
        fscanf(dic, "%s", new_node->word);
    
        if(feof(dic))
        {
            free(new_node);
            break;
        }
        
        // hash that word
        long key = hash(new_node->word);
    
        // add new node to head of list
        new_node->next = hashtable[key];
        hashtable[key] = new_node;
       
    }
    
    // close dictionary
    fclose(dic);
      
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return lines;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        //don't lose the rest of the list
        node* curr = hashtable[i];
        node* prev = NULL;    
    
        // free all of the nodes in a list
        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    return true;
}

/**
 * Returns hash value - the storage location of a given word
 */
unsigned long hash(char *str)
    {
        unsigned long hash = 5381;

         int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % 16908799) % HASH_SIZE;
    }
