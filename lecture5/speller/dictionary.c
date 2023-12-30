// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = ('Z' * LENGTH);

// Variable to count number of words in dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash input string
    int index = hash(word);

    // Create cursor and point to table, accessing table at the hashed location
    node *cursor = table[index];

    // Traverse linked list, comparing strings
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Return true if strings match (case-insensitively)
            return true;
        }
        else
        {
            // If strings do not match, advance to next node in linked list
            cursor = cursor->next;
        }
    }

    // After traversing the entire linked list, if the word was not found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Loop through each char in word, adding ASCII value until reach end of string
    int index = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        index += toupper(word[i]);
        i++;
    }

    // Account for values that may somehow be outside the hash table
    if (index > (N))
    {
        index = index % N;
    }

    // Return index, which is the hash value
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open dictionary file.\n");
        return false;
    }

    // Read words from dictionary file one by one
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create new node for word & copy word from scan into node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Inadequate memory available\n");
            return false;
        }
        strcpy(new->word, word);

        // Hash word to obtain a hash value
        int index = hash(word);

        // Insert node into hash table at that location
        new->next = table[index];
        table[index] = new;

        // Keep track of how many words entered into dictionary.
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Simply return the counter, which kept track every time a word was entered into the dictionary
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
