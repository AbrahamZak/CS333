/*This is a C program that takes in an input file of MIPS Assembly Language (MAL) and then depending
on the flag provided by the user, the output file will contain a list of labels of the MAL program
used as variables, a list of labels of the MAL program used for flow control, or both.
*/

/* Flag Options Include:
 -v: Produces a list of labels of the MAL source program used as variables in the output file
 -f: Produces a list of labels of the MAL source program used for flow control in the output file
 -b: Produces a list of both labels in the output file
 */

//  Abraham Zakharov
//  Unix Login ID: ay451227
//  Lab Instructor: Areeb Khan
//  Lab: Friday @ 1:40PM - 2:35PM

#include <stdio.h>
#include <string.h>

//All of our functions
int flagv (char inputFile[], char outputFile[]);
int flagf (char inputFile[], char outputFile[]);
int flagb (char inputFile[], char outputFile[]);

#define FLAG 1
#define IN_FILE_ARG 2
#define OUT_FILE_ARG 3
#define NUMARG 4

int main(int argc, const char * argv[]) {
    //Check for if the correct number of arguments were inputted
    if (argc != NUMARG) {
        printf("Usage: findpath flag infile outfile\n");
        fflush(stdout);
        return 0;
    }
    
    //Copy our arguments into variables for ease of use
    char flag[256];
    strcpy(flag, argv[1]);
    char inputFile[256];
    strcpy(inputFile, argv[2]);
    char outputFile[256];
    strcpy(outputFile, argv[3]);
    
    //Check flag inputted
    if (strcmp(flag, "-v") == 0){
        printf("The flag is -v\n");
        flagv(inputFile,outputFile);
    }
    else if (strcmp(flag, "-f") == 0){
        printf("The flag is -f\n");
        flagf(inputFile,outputFile);
    }
    else if (strcmp(flag, "-b") == 0){
        printf("The flag is -b\n");
        flagb(inputFile,outputFile);
    }
    else{
        printf("Invalid flag: flag options are -v, -f, -b\n");
    }
    
    return 0;
}

//Produces a list of labels of the MAL source program used as variables in the output file
int flagv (char inputFile[], char outputFile[]){
    
    //Pointers for our input file and our output file
    FILE *infile, *outfile;
    
    //Open the input file
    if ((infile = fopen(inputFile, "r")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for reading.\n", inputFile);
        fflush(stdout);
        return 0;
    }
    
    //Create the output file
    if ((outfile = fopen(outputFile, "w")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for writing.\n", outputFile);
        fflush(stdout);
        return 0;
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);

    return 0;
}

//Produces a list of labels of the MAL source program used for flow control in the output file
int flagf (char inputFile[], char outputFile[]){
    //Pointers for our input file and our output file
    FILE *infile, *outfile;
    
    //Open the input file
    if ((infile = fopen(inputFile, "r")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for reading.\n", inputFile);
        fflush(stdout);
        return 0;
    }
    
    //Create the output file
    if ((outfile = fopen(outputFile, "w")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for writing.\n", outputFile);
        fflush(stdout);
        return 0;
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    return 0;
}

//Produces a list of both labels in the output file
int flagb (char inputFile[], char outputFile[]){
    //Pointers for our input file and our output file
    FILE *infile, *outfile;
    
    //Open the input file
    if ((infile = fopen(inputFile, "r")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for reading.\n", inputFile);
        fflush(stdout);
        return 0;
    }
    
    //Create the output file
    if ((outfile = fopen(outputFile, "w")) == NULL) {
        //If it fails, let the user know
        printf("Could not open file %s for writing.\n", outputFile);
        fflush(stdout);
        return 0;
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    return 0;
}
