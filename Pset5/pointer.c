#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main (void)
{
   printf("Please enter some text:");
   char* input;
   input = (char *) malloc(25);
   scanf("%s", input);
   printf("Your text %s is located at memory address %x", input, *input);
   free(input);
}
