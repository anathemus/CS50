/**
*greedy.c
*
*Benjamin A. Burgess
*anathemus@gmail.com
*
*Gets input of monetary value from user then displays 
*least amount of coins it would take to arrive at said value
*/
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Finds out how much money is owed
    printf("O hai! How much change is owed?");
    float floatyMoney = GetFloat();
    
    // Check for negative numbers
    while (floatyMoney < 0.00)
    {
        printf("How much change is owed?");
        floatyMoney = GetFloat();
    }
    
    // convert floatyMoney to a rounded int to prevent possible errors working with "floats"
    int moolah = round(floatyMoney *100);
    
    // variables for the different types of coins
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    
    // adds up all the quarters until $0.24 or less
    while (moolah > 24)
    {
        moolah = (moolah - 25);
        quarters++;
    }
    
    // adds up all the dimes until $0.09 or less
    while (moolah > 9)
    {
        moolah = (moolah - 10);
        dimes++;
    }
    
    // adds a nickel if there's a possibility
    if (moolah > 4)
    {
        moolah = (moolah - 5);
        nickels++;
    }
    
    // adds the pennies (that take just over 2 cents each to make...)
    while (moolah > 0)
    {
        moolah = (moolah - 1);
        pennies++;
    }   
    
    // now to add all the coins and print the result
    int coins = (quarters + dimes + nickels + pennies);
    printf("%i\n", coins);
}
