/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int first = 0;
    int last = n - 1;
    int middle = (first+last)/2;
    // TODO: implement a searching algorithm
    for (int i = 0; i < n; i++)
 
    while (first <= last) 
    {
        if (values[middle] < value)
            first = middle + 1;
                
        else if (values[middle] == value) 
        {
            return true;
        }
        else
            last = middle - 1;
 
        middle = (first + last)/2;
   }
   
   if (first > last)
   {
       return false;
   }
   return false;   
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 1 ; i <= n - 1; i++) 
    {
        int j = i;
        int mtcup;
    
        while ( j > 0 && values[j] < values[j-1]) 
        {
            mtcup = values[j];
            values[j] = values[j-1];
            values[j-1] = mtcup;
 
            j--;
        }
    }
    return;
}
