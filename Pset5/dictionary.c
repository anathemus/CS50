/****************************************************************************
 * Benjamin Burgess
 * anathemus@gmail.com

 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

#include "dictionary.h"

#define MAX_CHARS 27


// counter for size function to display.
int numWords = 0;

void beFree(node* current);
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // sets the trie pointer to the root.
    node* current = root;

    int i = 0;

    // while not at the end of the word ...
    while(word[i] != '\0')
    {
        // remove case sensitivity
        int letter = tolower(word[i]);

        // if it's an apostrophe ...
        if (letter == '\'')
        {
            // credit to http://andrewke.org/problem-set-5/ for helping figure out the 's
            letter = 123;
        }    

        // if there's still letters in the word to be checked, keep going.
        if (current->children[letter-'a'] != NULL)
        {
            current = current->children[letter-'a'];
            i++;
        }
        
        // otherwise it's a misspelled word.
        else
        {
           return false;
        }
    }

    // if you reach the end of the word with the boolean verification, then it's correctly spelled.
    if (current->is_word == true)
    {
       return true;

    }

    return false;
 }


/**
 * Loads dictionary into memory.  Returns true if successful else false.
*/

bool load(const char* dictionary)
{

    // open the dictionary, make a pointer to follow along
    FILE* inptr = fopen(dictionary, "r");

    // if something bad happens, close up shop.
    if(inptr == false)
    {
       fclose(inptr);
       return false;
    }    

    // malloc for the root, set trie pointer to nada

    root = malloc(sizeof(node)); 
    node* current = NULL;

    int n = 0;

    // while you haven't reached the end of the file... keep reading!
    while(fgetc(inptr) != EOF)
   {
       // go back one to the beginning of the word.
       fseek(inptr, -1, SEEK_CUR);
       
       // set the pointer to the root
       current = root;
       
       // iterate through until new line
       for(n = fgetc(inptr); n != '\n'; n = fgetc(inptr))
       {
            // credit to http://andrewke.org/problem-set-5/ for helping figure out the 's
            if (n == '\'')
            {
                n = 123;
            }
            
            // if next node doesn't exist, malloc and create it in the trie
            if(current->children[n-'a'] == NULL)
            {
                current->children[n-'a'] = malloc(sizeof(node));
                current = current->children[n-'a'];
            }
            
            // else add character to the trie
            else
            {
                current = current->children[n-'a'];
            }
               
        }
        
        // at the end of the word, add the boolean tag to verify that it is indeed a word!
        current->is_word = true;
        numWords++;
    }    

    fclose(inptr);
    return true;    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (numWords > 0)
    {
        return numWords;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if (root != NULL)
    {
        beFree(root);
        return true;
    }
    else
    {
        return false;
    }
}

// function to free everything! The best things in life are free! (the best code too)
void beFree(node* current)
{
    for (int i = 0; i < MAX_CHARS; i++)
    {
        if(current->children[i] != NULL)
        {
            // recursion call to free all the things!
            beFree(current->children[i]);
        }
    }
    free(current);
}    

