/**
*insertion.c
*
*Benjamin A. Burgess
*anathemus@gmail.com
*
*Gets integers from user, sorts them, prints sorted list to screen.
*/

#include <stdio.h>
#include <cs50.h>

void sorter(int list[], int size);

int main(void)
{
    int MAX = 20000;    
    int sort[MAX];
    int n;  
    printf("Please enter numbers to sort: \n");
    
    for (n = 0; n < MAX; n++)
    {
        printf("sort[%i] =", n);
        
        // Gets user input integers, if Ctrl-D end of file command used, breaks.
        int input = GetInt();
        printf("\n");
        
        if (input == INT_MAX)
        {
            break;
        }
        
        sort[n] = input;
    
    }
    
    printf("Now to sort your numbers!\n");
    
    sorter(sort, n);
    
    printf("\n");
}

// Function sorts the list of integers and prints the sorted list.

void sorter(int list[], int size)
{

    for (int i = 1; i < size; i++)
    {
        int j = i;
        int sortvar;
        
        while (j > 0 && list[j] < list[j-1])
        {
            //puts the [j-1]th integer into the sorting variable
            
            sortvar = list[j-1];
            
            //puts the [j]th integer into the [j-1]th spot
            
            list[j-1] = list[j];
            
            //puts the sorting variable's contents(the smaller number) into the [j]th spot
            
            list[j] = sortvar;
            
            //iterates back through to make sure everything is sorted
            
            j--;
        }
    }
    
    // now to print!
    printf("Your sorted list is as follows:\n");
    
    for (int k = 0; k < size; k++)
    {
        printf("%i, ", list[k]);
    }
}
