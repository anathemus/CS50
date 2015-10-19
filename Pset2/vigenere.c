/**
*vigenere.c
*
*Benjamin A. Burgess
*anathemus@gmail.com
*
* gets input from user, encrypts according to a codeword
* and prints encrypted characters from user input to screen.
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// gives the program a heads up that I'll be using this function later.
char encryption(char decode, int ring);

int main(int argc, string argv[])
{
    /* checks to make sure that the command line argument is not
    * NULL nor greater than 1
    */
    if (argv[1]!=NULL && argc <= 2)
    {
        string command = argv[1];
        int ring [strlen(command)];
        
        // a for iteration to make sure all characters are alpha
        for (int n = 0, m = strlen(command); n < m; n++)
        {
            if ((isalpha(command[n]))==0)
            {
                printf("\n");
                return 1;
            }
            
        }
        
        string decode = GetString();
                
        // creates integer to encrypt characters
        
        for (int i=0, n=0; i < strlen(decode); i++)
        {
            // if the encryption codeword has reached the end, start back at the beginning.
            n = n%(strlen(command));
            // if/else statement to set A and a to 0, B and b to 1, etc.
            if (isupper(command[n]))
            {
                ring[i] = (((int)command[n])-'A');
                
            }
            else
            {
                ring[i] = (((int)command[n])-'a');
                
            }
            
            // checks to see if it's capital.
            if (isalpha(decode[i]))
            {
                printf("%c", encryption(decode[i], ring[i]));
                n++;
            }
            else
            {
                printf("%c", decode[i]);
            }
             
        }
        printf("\n");
    }
    else
    {
        printf("\n");
        return 1;
    }
}
char encryption(char decode, int ring)
{
    if (isupper(decode))
    {
        return ((((int)decode-'A')+ring) %26 + 'A');
    }
    else
    {
        return ((((int)decode-'a')+ring) %26 + 'a');
    }

}
