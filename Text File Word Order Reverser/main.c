/*
 This is a simple C program that takes in an input text file
 and reverses the order of the words in each line. It also
 removes any excess tabs and spaces from the original input file,
 leaving one space between each word. The program then writes
 the result into an output file. Both the input file and output
 file are specified by the user as arguments.

 */

//  Abraham Zakharov
//  Unix Login ID: ay451227
//  Lab Instructor: Areeb Khan
//  Lab: Friday @ 1:40PM - 2:35PM


#include <stdio.h>
#include <string.h>

/* The longest a line in the txt file can be */
#define MAXLEN 255

#define IN_FILE_ARG 1
#define OUT_FILE_ARG 2
#define NUMARG 3

int main(int argc, const char * argv[]) {
    //Pointers for our input file and our output file
    FILE *infile, *outfile;
    
    //Check for if the correct number of arguments were inputted
    if (argc != NUMARG) {
        printf("Usage: findpath infile outfile\n");
        fflush(stdout);
        return 0;
    }
    
    //Add .txt to the end of the input file name and output file name
    char inputFile[256];
    strcpy(inputFile, argv[1]);
    strcat(inputFile, ".txt");
    
    char outputFile[256];
    strcpy(outputFile, argv[2]);
    strcat(outputFile, ".txt");
    
    //Open the input file
    if ((infile = fopen(inputFile, "r")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s.txt for reading.\n", argv[IN_FILE_ARG]);
        fflush(stdout);
        return 0;
    }
    
    //Create the output file
    if ((outfile = fopen(outputFile, "w")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s.txt for writing.\n", argv[OUT_FILE_ARG]);
        fflush(stdout);
        return 0;
    }
    
    /*
     Now that we've opened both files successfully, we need to
     reverse the lines from our input and place them into the output
    */
    char line [MAXLEN];
    
    //We begin by taking an input line by line
    while (fgets(line, MAXLEN, infile) != NULL) {
        
        //Remove the newline character from the input line
        strtok(line, "\n");
        
        /*First, we reverse the entire line
         For example the line: Here's     Johnny
                  will become: ynnoJ      s'ereH
         */
        int index = 0;
        long endOfLine = strlen(line)-1;
        char reversedLine [MAXLEN];
        while (endOfLine>-1){
            reversedLine[index] = line[endOfLine];
            index++;
            endOfLine--;
            }
        reversedLine[index] = '\0';
        
        /*We then remove an excess spaces from the line
         For example the line: ynnoJ      s'ereH
                      becomes: ynnoJ s'ereH
         
         Here, we also convert all \t (tabs) in our original input into spaces
         while also converting all extra spaces into a single space
         */
        char reversedLineNoExtraSpaces [MAXLEN];
        int originalPosition = 0;
        int extraSpaceRemovePosition = 0;
        
        while (reversedLine [originalPosition] != '\0'){
            if (reversedLine [originalPosition] == ' ' && reversedLine [originalPosition+1] == ' '){
                originalPosition++;
            }
            if (reversedLine [originalPosition] == '\t'){
                reversedLineNoExtraSpaces[extraSpaceRemovePosition] = ' ';
                extraSpaceRemovePosition++;
                originalPosition++;
                continue;
            }
            else{
                reversedLineNoExtraSpaces[extraSpaceRemovePosition] = reversedLine[originalPosition];
                originalPosition++;
                extraSpaceRemovePosition++;
            }
        }
        reversedLineNoExtraSpaces[extraSpaceRemovePosition] = '\0';
        
        /* We do what we just did one more time in order to remove excess spaces
         created by the tabs that we converted
         */
        char reversedLineNoExtraSpacesFromTabs [MAXLEN];
        originalPosition = 0;
        extraSpaceRemovePosition = 0;
        while (reversedLineNoExtraSpaces [originalPosition] != '\0'){
            if (reversedLineNoExtraSpaces [originalPosition] == ' ' && reversedLineNoExtraSpaces [originalPosition+1] == ' '){
                originalPosition++;
            }
            else{
                reversedLineNoExtraSpacesFromTabs[extraSpaceRemovePosition] = reversedLineNoExtraSpaces[originalPosition];
                originalPosition++;
                extraSpaceRemovePosition++;
            }
        }
        reversedLineNoExtraSpacesFromTabs[extraSpaceRemovePosition] = '\0';
        
        /* Now, we can finally reverse each word individually to get our final result
         For example the line: ynnoJ s'ereH
                      becomes: Jonny Here's
         */
        char finalResult [MAXLEN];
        int startWord = 0;
        int endWord = 0;
        int finalPosition = 0;
        
        while (reversedLineNoExtraSpacesFromTabs [endWord] != '\0'){
            
            if (reversedLineNoExtraSpacesFromTabs[endWord+1]!= ' '){
                endWord++;
            }
            
            if (reversedLineNoExtraSpacesFromTabs[endWord+1]== ' ' || reversedLineNoExtraSpacesFromTabs[endWord+1]== '\0'){
                int i = endWord;
                while (i+1!=startWord){
                    finalResult[finalPosition] = reversedLineNoExtraSpacesFromTabs[i];
                    i--;
                    finalPosition++;
                }
                finalResult[finalPosition] = ' ';
                finalPosition++;
                startWord = endWord + 2;
                endWord++;
            }
        }
        
        finalResult[finalPosition] = '\n';
        finalResult[finalPosition+1] = '\0';

        //When finished reversing each word, we put the line into our output file
        fputs(finalResult,outfile);
        
    }
        

    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    
    printf ("Finished.\n");
    fflush(stdout);
    
    return 0;
}


