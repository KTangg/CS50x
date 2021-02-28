// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 14000;

// Hash table
node *table[N];

// Declare word count to begin when dict load
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //hash to obtain table index
    unsigned int index = hash(word);

    //point to the word
    node *cursor = table[index];

    //check the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }

        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
        {
            return false;
        }

    //read a word(string) from dict
    char dict_word[LENGTH + 1];

    while (fscanf(dict, "%s", dict_word) != EOF)
    {
        //create new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
        n -> next = NULL;

        strcpy(n -> word, dict_word);

        //use hash f(x) to detemine the index on node table
        unsigned int index = hash(n -> word);


        if (table[index] == NULL)
        {
            table[index] = n;
            word_count += 1;
        }

        //link new node to the existing one
        else if (table[index] != NULL)
        {
            n -> next = table[index];
            table[index] = n;
            word_count += 1;
        }
    }



    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *tmp;
        node *cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;

            cursor = cursor -> next;

            free(tmp);
        }
    }

    return true;
}
