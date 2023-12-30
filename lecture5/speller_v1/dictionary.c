// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Create variables to be used across functions
node *list = NULL;
long int wordcount = 0;

// TODO: Choose number of buckets in hash table
// # buckets in hash table = number of letters * maximum length
const unsigned int N = (122 * LENGTH);

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);                    // Find index of word
    node *llist = table[index];                         // create pointer to this arm of the hash table
    while (llist != NULL)                               // Loop until at end of linked list
    {
        if (strcmp(llist->word, word) == 0)             // If word is found return true
        {
            return true;
        }
        else
        {
            if (llist->next != NULL)                    // If not last node in arm
            {
                llist = llist->next;                    // Move to next node
            }
        }
    }
    return false;                                       // If not found ever, return false.
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int asciitotal = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        char lower = tolower(word[i]);
        asciitotal = asciitotal + lower;
    }
    return asciitotal;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Unable to open dictionary\n");
        return false;
    }

    // Read dictionary into a linked list
    node *read = malloc(sizeof(node));              // Create node for read word
    while (fscanf(dict, "%s", read->word) != EOF)   // Loop until at end of dictionary, reading one word at a time into read node
    {
        node *new = malloc(sizeof(node));           // Create new node
        strcpy(new->word, read->word);              // Copy read word to new word
        new->next = list;                           // Make new node point to list (previous node)
        list = new;                                 // Make list point to the newest created node (thus pointing to the entire linked list)
    }
    free(read);                                     // Free created temporary node

    // Enter each word from linked list into hash table
    while (list->next != NULL)                      // Repeat until reaches the end of the dictionary linked list
    {
        unsigned int index = hash(list->word);      // Get hash index value
        if  (table[index] == NULL)                  // If 1st node in index
        {
            table[index] = malloc(sizeof(node));    // Malloc node for index
            table[index]->next = list->next;        // Point index to current node in hash table
            list = list->next;                      // Point list to next node
            table[index]->next = NULL;              // Set node->next to NULL
            wordcount++;                            // Increase word count counter
        }
        else                                        // If not 1st node in index
        {
            node *temp = table[index];              // Point temp to previous node in index
            table[index] = list;                    // Point index to current node in hash table
            list = list->next;                      // Point list to next node
            table[index]->next = temp;              // Point new node->next to temp (next node in hash table)
            wordcount++;                            // Increase word count counter
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = malloc(sizeof(node));
    for (int i = 0; i < (122 * LENGTH) + 1; i++)
    {
        list = table[i];
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free (ptr);
            ptr = next;
        }
    }
    return true;
}
