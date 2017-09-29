/*
 Program to convert a decimal number inputted by the user into
 its representation in radix of the second number inputted by the user
*/

//  Abraham Zakharov
//  Unix Login ID:
//  Lab Instructor:
//  Lab: Friday @

#include <stdio.h>

int main(int argc, const char * argv[]) {
    //The two main ints we will be using, the base number, and the radix
    int number;
    int radix;
    
    //Ask the user to input their choice of two numbers
    printf("Please input two numbers.\n");
    fflush(stdout);
    
    //Take the two number inputs and assigns them to number and radix
    scanf ("%d%d", &number, &radix);
    
    //Counter for how many times we are dividing the number by the radix
    char count = 0;
    //A set of base characters because we cannot use numbers past 9 so we use letters to substitute
    char baseChars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //A character array for the result
    char result [50];
    
    //A while loop until our number reaches 0
    while (number != 0){
        /*We take the modulus (remainder) and put it into our result array in terms of our base characters, then we divide the number by the radix, and increment the count by one*/
        result[count] = baseChars[number%radix];
        number = number / radix;
        if (number == 0){
            break;
        }
        count ++;
    }
    
    /*Once we have our results we need to reverse it. So, we create a new char array in the size of
    our count minus 1, and we create an int i to count the transfer places in the new array*/
    char resultReversed [count-1];
    int i = 0;
    //We loop in the amount of our count so all data is copied from our result array into our reverse result array
    while (count >= 0){
        resultReversed[i] = result[count];
        //Every time we copy data we decrement count by 1 and increment i by 1
        count --;
        i++;
    }
    
    //Print the result
    printf("Result: %s \n", resultReversed);
    fflush(stdout);
    
    return 0;
}
