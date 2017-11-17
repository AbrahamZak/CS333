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

//  Lance Ackerson
//  Unix Login ID: LA444978
//  Lab Instructor:
//  Lab: Wednesday 4:15

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

#define MAXLEN 80

/* We use two structs, node is a linked list, id simply holds the identifier
 and points to a node*/
struct node {
    char text [255];
    struct node *next;
};

struct id {
    char identifier [11];
    struct node *next;
};

struct id flow[100];
int flowCount = 0;

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
        flagv(inputFile,outputFile);
    }
    else if (strcmp(flag, "-f") == 0){
        flagf(inputFile,outputFile);
    }
    else if (strcmp(flag, "-b") == 0){
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
    
    //A string that will store each line we read from the input file
    char line [MAXLEN];
    
    //Get each line of the MAL program and process them until we reach the end
    while (fgets(line, MAXLEN, infile) != NULL) {
        
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
    
    //A string that will store each line we read from the input file
    char line [MAXLEN];
    
    //Indicator of if we have passed the .data section and reached the .text section
    int passedData = 0;
    
    //Get each line of the MAL program and process them until we reach the end
    while (fgets(line, MAXLEN, infile) != NULL) {
        //Skip comments and whitespace lines
        if (line[0] == '#' || line [0] == '\n'){
            continue;
        }
        //This is to check if the current line contains .text, if it does, we have passed the data section
        char *check = strstr(line, ".text");
        if (check){
            passedData = 1;
        }
        if (passedData == 0){
            continue;
        }
        
        /*For all lines past the .data section we check for : , if found we know all previous
        text is our identifier so we copy it over to our array of identifiers*/
        long len = strlen(line);
        int i;
        for (i=0; i<len; i++){
            if (line[i] == ':'){
                strncpy(flow[flowCount].identifier, line, i);
                flowCount++;
                break;
            }
        }
    }
    
    //Now we input all of our identifiers and their mentioned lines into our output file
    int i = 0;
    for (i=0; i<flowCount; i++){
        char tagged [100] = "Flow Control ID –";
        strcat(tagged,flow[i].identifier);
        strcat(tagged, "–\n");
        fputs(tagged, outfile);
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
    
    //A string that will store each line we read from the input file
    char line [MAXLEN];
    
    //Get each line of the MAL program and process them until we reach the end
    while (fgets(line, MAXLEN, infile) != NULL) {
        
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    return 0;
}
