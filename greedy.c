/*
 *greedy.C
 *
 *Evan Gatchell
 *
 *A program that takes an amount of money 
 *and gives you the least amount of coins 
 *as change.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float a;
    do
    {
        // Prompt user for input
        
        printf("Please enter a dollar amount: ");
        a = GetFloat(); 
    }
    while (a < 0);      
    {   
        // Converts into cents, trickles down remainders 
        
        int total = round(a * 100);
        int quarters = total / 25;
        int qm = total % 25;    
        int dimes = qm / 10;
        int dm = qm % 10;
        int nickles = dm / 5;
        int nm = dm % 5;
        int pennies = nm / 1;
        
        int coins = quarters + dimes + nickles + pennies;              
        
        printf("%d\n", z);
    }           
}
