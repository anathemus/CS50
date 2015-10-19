/**
*mario.c
*
*Benjamin A. Burgess
*anathemus@gmail.com
*
*Makes a half pyramid like Mario uses in many Mario Bros levels
*/
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Height: ");
    
    int height;
    height = GetInt();
    string bricks = "########################";
    string space = "                       ";
    
   
    
    /** Eef itsa to high or too low! Mario worka too hard plumbing alla day 
    *to be climba de stairs so much! Mama mia!
    */
	while ((height > 23) || (height <0)) 
	{
		printf("Height: ");

		height = GetInt();
	}
	
	int count = (height - 1);
	
	// Deesa where de magic happens! I makea de stairs!
	for (int n = 2; n <= (height + 1); n++)
	{
	    printf("%.*s", count, space);
	    printf("%.*s", n, bricks);
	    printf("\n");
		count--;		
	}
}
