// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char word_check[LENGTH + 1];

    for(int i = 0; i < LENGTH + 1; i++)
    {
        word_check[i] = tolower(word[i]);
    }

    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if(strcmp(word_check, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char first_letter = toupper(word[0]);
    int hash_value = first_letter - 65;

    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //open dictionnary file
    FILE *load_dictionary;

    load_dictionary = fopen(dictionary, "r");

    //check for error
    if (load_dictionary == NULL)
    {
        return false;
    }

    char current_word[LENGTH + 1];

    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //read string from file one by one
    while(fscanf(load_dictionary, "%s", current_word) != EOF)
    {
        //create a node for each word
        node *new_entry = malloc(sizeof(node));

        strcpy(new_entry->word, current_word);
        new_entry->next = NULL;

        //hash word to obtain value
        //insert node into hash table second_hash correct linked list
        if (table[hash(current_word)] == NULL)
        {
            table[hash(current_word)] = new_entry;
        }
        else
        {
            node *last_node = table[hash(current_word)];

            while(last_node->next != NULL)
            {
                last_node = last_node->next;
            }
            last_node->next = new_entry;
        }
    }
    fclose(load_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int word_count = 0;

    for (int i = 0; i < N; ++i)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            word_count++;
        }
    }
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; ++i)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        if(table[i] != NULL)
        {
            return false;
        }
    }
    return true;
}
