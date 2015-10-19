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

int main(int argc, string argv[])
{
    if (argv[1]!=NULL)
    {
        string decode = GetString();
                
        // creates integer to encrypt characters
        int ring = ((atoi(argv[1]))%26);
        
        
        for (int i=0, encryption=0; i < strlen(decode); i++)
        {
            // checks to see if it's a letter, otherwise just prints the character.
            if (isalpha(decode[i]))
            {
                // neater to store this formula in a value than to copy/paste.
                encryption = ((int)decode[i]+ring);
            
                /**
                * checks to see if key+ASCII value is still an alpha character.
                * If not, wraps it back to the beginning of the alphabet of the same case.
                */
            
                if (isalpha(encryption))
                {
                    printf("%c", (char)encryption);
                }
                else
                {
                    encryption = (encryption-26);
                    
                    printf("%c", (char)encryption);
                }
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
