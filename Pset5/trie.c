typedef struct node

{
    bool is_word;
    struct node* children[27];
} 
node;

node* root;

int nwords = 0;

/**
* Returns true if word is in dictionary else false.
*/

bool check(const char* word)
{
    node* current = root;

    int i = 0;

    while(word[i] != '\0')
    {
        int letter = tolower(word[i]);

        if (letter == '\'')
        {
            return false;
        }    

        if (current->children[letter-'a'] != NULL)
        {
            current = current->children[letter-'a'];
            i++;
        }

        else
        {
           return false;
        }
    }

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

    FILE* dict = fopen(dictionary, "r");

    if(dict == false)
    {
       return false;
    }    

    //initialize nodes

    root = calloc(27,sizeof(node)); 
    node* current = NULL;

    int c = 0;

    while(fgetc(dict) != EOF)
   {
       fseek(dict, -1, SEEK_CUR); //go back one byte to beginning of word
       current = root; //set index to root

       for(c = fgetc(dict); c != '\n'; c = fgetc(dict)) //iterate through word
       {
            if(current->children[c-'a'] == NULL)
            {
                current->children[c-'a'] = calloc(27,sizeof(node));
                current = current->children[c-'a'];
            }
            else
            {
                current = current->children[c-'a'];
            }       
        }
        current->is_word = true; //once line break reached end the word
        nwords++;
    }    

    fclose(dict);
    return true;    
}

/**
* Returns number of words in dictionary if loaded else 0 if not yet loaded.
*/

unsigned int size(void)
{
    return nwords;
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

void freeNode(node* current)
{
    for (int i = 0; i < 27; i++)
    {
        if(current->children[i] != NULL)
        {
            freeNode(current->children[i]);
        }
    }
    free(current);
}    

bool unload(void)
{
    freeNode(root);  
    return true;
}
