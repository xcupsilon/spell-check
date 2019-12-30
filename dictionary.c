// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

void destroy(node* tries);
// Represents a trie
node *root;
node *trav;
int result = 0;
int dictionarySize = 0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }
    trav = root;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    int i;
    while (fscanf(file, "%s", word) != EOF)
    {
        i = 0;
        do // Insert words into trie
        {
            if (word[i] != '\0') // Check if reached the end of the word
            {
                if (word[i] != '\'') // Check if it is the character of apostrophe
                {
                    int tmp = tolower(word[i]);  // Convert the letter into lowercased ASCII integer
                    tmp %= 97; // Calculate the number in the alphabet where the character belongs to
                    if (trav->children[tmp] == NULL) // Check if the character is already stored in a trie
                    {
                        trav->children[tmp] = malloc(sizeof(node)); // If not, allocate new node to store the character
                        if (trav->children[tmp] == NULL) // Check for NULL
                        {
                            return false;
                        }
                        trav = trav->children[tmp]; // Moves the cursor forward into new node
                        trav->is_word = false; // Initiliaze the node to not be a word
                        for (int j = 0; j < N; j++) // Initiliaze children nodes to be NULLs
                        {
                            trav->children[j] = NULL;
                        }
                    }
                    else
                    {
                        trav = trav->children[tmp]; // Move the cursor forward into the node that already exists
                    }
                }
                else
                {
                    if (trav->children[26] == NULL) // Check if the children node for apostrophe is blank
                    {
                        trav->children[26] = malloc(sizeof(node)); // Allocate memory for new node if so
                        if (trav->children[26] == NULL) // Check for NULL
                        {
                            return false;
                        }
                        trav = trav->children[26]; // Move the cursor forward
                        trav->is_word = false; // Initialize the node to not be a word
                        for (int j = 0; j < N; j++) // Initiliaze children nodes to be NULLs
                        {
                            trav->children[j] = NULL;
                        }
                    }
                    else
                    {
                        trav = trav->children[26]; // Move the cursor forward into the node that already exists
                    }
                }
                i++; // Move onto the next character in the word
            }
        }
        while (word[i] != '\0'); // Repeat the process until reached the end of the word
        trav->is_word = true; // Change the condition of the current node to be a word
        dictionarySize++; // Increase dictionary size by one
        trav = root; // Reset the cursor to the root
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    result = 1;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (result == 1)
    {
        return dictionarySize;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int i = 0;
    trav = root; // Reset cursor
    do
    {
        if (word[i] != '\0') // Check if reached the end of the word
        {
            if (word[i] != '\'') // Check if the character is a apostrophe
            {
                int tmp = tolower(word[i]); // Convert the character to lowercased, represented by its value in ASCII
                tmp %= 97; // Calculate the number in the alphabet where the character belongs to
                if (trav->children[tmp] == NULL) // Check if the corresponding node to the character exists or not
                {
                    return false; // Then not a word that exists in the dictionary
                }
                else
                {
                    trav = trav->children[tmp]; // Move onto the next node for checking
                }
            }
            else
            {
                if (trav->children[26] == NULL) // Check if the node corresponds to apostrophe exists or not
                {
                    return false; // Then not a word that exists in the dictionary
                }
                else
                {
                    trav = trav->children[26]; // Move the cursor forward
                }
            }
            i++; // Move onto the next character in the word
        }
    }
    while (word[i] != '\0'); // Repeat the process until reached the end
    if (trav->is_word == false) // Check if the bottom node is not representing the end of a word in the dictionary
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    trav = root; // Reset the cursor to root position
    destroy(trav);
    free(root); // Free root node
    return true;
}

void destroy(node* tries) // Free all children nodes
{
    for (int i = 0; i < N; i++) // Repeat the process for each of the 27 children nodes
    {
        if (tries->children[i] != NULL) // Check if reached the bottom of the remaining tries
        {
            destroy(tries->children[i]); // Call for recursive destruction from the buttom of the tries
        }
        free(tries->children[i]); // Free children node
    }
}
