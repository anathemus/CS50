/**
*initials.c
*
*Benjamin A. Burgess
*anathemus@gmail.com
*
*Gets name input from user, outputs their initials capitalized
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string Initialize(string);

int main(void)
{
    // get their name, print the initials
    string name = GetString();
    
    if (name != NULL)
    {
    /**
    * checks first character of string. if its a letter, prints it.
    * makes it Capital if need be.
    */
    if (isalpha(name[0]))
        printf("%c", toupper(name[0]));
            
    // loop to count and get other initials 
    for (int n = 0, l = strlen(name); n < l; n++)
    {
    // checks for spaces, then prints next character as a Capital letter.
        if ( isspace (name[n]))
        {
           n++;
           printf("%c", toupper((char)name[n]));
        }    
    }
        printf("\n");
    }
}
