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
//  Lab: Wednesday 4:15

/*
 TEAM PROJECT DEVELOPMENT
 flagv and all related testing: Lance Ackerson
 flagf and all related testing: Abraham Zakharov
 flagb and main with all related testing: Both
 Structs and public variables and related testing: Both
 */

#include <stdio.h>
#include <stdlib.h>
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
    char text [MAXLEN];
    struct node *next;
};

struct id {
    char identifier [11];
    struct node *head;
};

//Array for the flow identifiers and a counter
struct id flow[100];
int flowCount = 0;

//Array for the variable identifiers and a counter
struct id stream[100];
int streamCount = 0;

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
    //indicator for when we have reached .data section
    int data = 0;
    //Get each line of the MAL program and process them until we reach the end
    while (fgets(line, MAXLEN, infile) != NULL) {
        //Skip comments and whitespace lines
        if (line[0] == '#' || line [0] == '\n'){
            continue;
        }
        //to check if we've passes data section
        char *checkText = strstr(line, ".text");
        //loop is broken once we've passed data section
        if(checkText){
            break;
        }
        
        char *check = strstr(line, ".data");
        if (check){
            data = 1;
        }
        if (data == 0){
            continue;
        }
        
        long leng = strlen(line);
        int j;
        for(j = 0; j < leng; j++){
            if(line[j] == ':'){
                strncpy(stream[streamCount].identifier, line, j);
                streamCount++;
                break;
            }
        }
    }
    int firstRef = 0;
    int j = 0;
    for(j = 0; j < streamCount; j++){
        //Go to beginning of file
        rewind(infile);
        //reset our data field
        data = 0;
        firstRef = 0;
        while (fgets(line, MAXLEN, infile) != NULL) {
            //Skip comments and whitespace lines
            if (line[0] == '#' || line [0] == '\n'){
                continue;
            }
            
            //Check if we've hit our first reference
            if (data==1){
                char *checker = strstr(line, ":");
                if (checker){
                    //Set our first reference variable to 1
                    firstRef = 1;
                }
            }
            
            
            //This is to check if the current line contains .text, if it does, we have passed the data section
            char *checkData = strstr(line, ".text");
            if (checkData){
                data = 1;
            }
            if (data == 0){
                continue;
            }
            
            if (firstRef == 0){
                continue;
            }
            //If we find a line in our input that contains the identifier, we copy that line to the
            //identifiers linked list
            char *foundID = strstr(line, stream[j].identifier);
            if (foundID){
                //create a node
                struct node *add = (struct node*) malloc(sizeof(struct node));
                strcpy(add->text, line);
                add->next = NULL;
                
                //If there is no lines on the list yet, make this line the head
                if (stream[j].head==NULL){
                    stream[j].head = add;
                }
                else{
                    struct node *current = stream[j].head;
                    while(current->next!=NULL){
                        current = current->next;
                    }
                    current->next=add;
                }
            }
        }
    }
    //Now we input all of our identifiers and their mentioned lines into our output file
    j = 0;
    for (j=0; j<streamCount; j++){
        //Add "" into the file
        char tagged [100] = "Variable ID –";
        strcat(tagged,stream[j].identifier);
        strcat(tagged, "–\n");
        fputs(tagged, outfile);
        
        
        //Iterate through linked list for specific identifier and add lines to output file
        if (stream[j].head==NULL){
        }
        else{
            struct node *current = stream[j].head;
            fputs(stream[j].head->text,outfile);
            while (current->next!=NULL){
                current = current->next;
                fputs(current->text,outfile);
            }
        }
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    printf("done\n");
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
    
    //Get each line of the MAL program and process them until we reach the end and find all identifiers
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
    
    /*This time we read each line of the file again for each identifier we previously found
     as we cycle through the file each time we search for the identifier on a line and if found
     we copy that line over to that identifier's next node pointer on the struct's linked list
     */
    //Marker for the first reference of any flow identifier in our program
    int firstReference = 0;
    int i = 0;
    for (i=0; i<flowCount; i++){
        //Go back to beginning of our input file
        rewind(infile);
        //Reset passedData
        passedData = 0;
        //Reset firstReference
        firstReference = 0;
        while (fgets(line, MAXLEN, infile) != NULL) {
            //Skip comments and whitespace lines
            if (line[0] == '#' || line [0] == '\n'){
                continue;
            }
            
            //Check if we've hit our first reference
            if (passedData==1){
                char *checking = strstr(line, ":");
                if (checking){
                    //Set our first reference variable to 1
                    firstReference = 1;
                }
            }
            
            //Skip lines containing : because we are done with finding the identifiers
            char *check = strstr(line, ":");
            if (check){
                continue;
            }
            //This is to check if the current line contains .text, if it does, we have passed the data section
            char *checkData = strstr(line, ".text");
            if (checkData){
                passedData = 1;
            }
            if (passedData == 0){
                continue;
            }
            
            if (firstReference == 0){
                continue;
            }
            //If we find a line in our input that contains the identifier, we copy that line to the
            //identifiers linked list
            char *foundID = strstr(line, flow[i].identifier);
            if (foundID){
                //create a node
                struct node *add = (struct node*) malloc(sizeof(struct node));
                strcpy(add->text, line);
                add->next = NULL;
                
                //If there is no lines on the list yet, make this line the head
                if (flow[i].head==NULL){
                    flow[i].head = add;
                }
                else{
                    struct node *current = flow[i].head;
                    while (current->next!=NULL){
                        current = current->next;
                    }
                    current->next=add;
                }
            }
        }
    }
    
    //Now we input all of our identifiers and their mentioned lines into our output file
    i = 0;
    for (i=0; i<flowCount; i++){
        //Add "Flow Control ID -Identifier-" into the file
        char tagged [100] = "Flow Control ID –";
        strcat(tagged,flow[i].identifier);
        strcat(tagged, "–\n");
        fputs(tagged, outfile);
        
        //Iterate through linked list for specific identifier and add lines to output file
        if (flow[i].head==NULL){
        }
        else{
            struct node *current = flow[i].head;
            fputs(flow[i].head->text,outfile);
            while (current->next!=NULL){
                current = current->next;
                fputs(current->text,outfile);
            }
        }
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
    
    /*
     VARIABLE SECTION
     */
    
    //A string that will store each line we read from the input file
    char line [MAXLEN];
    //indicator for when we have reached .data section
    int data = 0;
    //Get each line of the MAL program and process them until we reach the end
    while (fgets(line, MAXLEN, infile) != NULL) {
        //Skip comments and whitespace lines
        if (line[0] == '#' || line [0] == '\n'){
            continue;
        }
        //to check if we've passes data section
        char *checkText = strstr(line, ".text");
        //loop is broken once we've passed data section
        if(checkText){
            break;
        }
        
        char *check = strstr(line, ".data");
        if (check){
            data = 1;
        }
        if (data == 0){
            continue;
        }
        
        long leng = strlen(line);
        int j;
        for(j = 0; j < leng; j++){
            if(line[j] == ':'){
                strncpy(stream[streamCount].identifier, line, j);
                streamCount++;
                break;
            }
        }
    }
    int firstRef = 0;
    int j = 0;
    for(j = 0; j < streamCount; j++){
        //Go to beggining of file
        rewind(infile);
        //reset our data field
        data = 0;
        firstRef = 0;
        while (fgets(line, MAXLEN, infile) != NULL) {
            //Skip comments and whitespace lines
            if (line[0] == '#' || line [0] == '\n'){
                continue;
            }
            
            //Check if we've hit our first reference
            if (data==1){
                char *checker = strstr(line, ":");
                if (checker){
                    //Set our first reference variable to 1
                    firstRef = 1;
                }
            }
            
            
            //This is to check if the current line contains .text, if it does, we have passed the data section
            char *checkData = strstr(line, ".text");
            if (checkData){
                data = 1;
            }
            if (data == 0){
                continue;
            }
            
            if (firstRef == 0){
                continue;
            }
            //If we find a line in our input that contains the identifier, we copy that line to the
            //identifiers linked list
            char *foundID = strstr(line, stream[j].identifier);
            if (foundID){
                //create a node
                struct node *add = (struct node*) malloc(sizeof(struct node));
                strcpy(add->text, line);
                add->next = NULL;
                
                //If there is no lines on the list yet, make this line the head
                if (stream[j].head==NULL){
                    stream[j].head = add;
                }
                else{
                    struct node *current = stream[j].head;
                    while(current->next!=NULL){
                        current = current->next;
                    }
                    current->next=add;
                }
            }
        }
    }
    //Now we input all of our identifiers and their mentioned lines into our output file
    j = 0;
    for (j=0; j<streamCount; j++){
        //Add "" into the file
        char tagged [100] = "Variable ID –";
        strcat(tagged,stream[j].identifier);
        strcat(tagged, "–\n");
        fputs(tagged, outfile);
        
        
        //Iterate through linked list for specific identifier and add lines to output file
        if (stream[j].head==NULL){
        }
        else{
            struct node *current = stream[j].head;
            fputs(stream[j].head->text,outfile);
            while (current->next!=NULL){
                current = current->next;
                fputs(current->text,outfile);
            }
        }
    }
    
    /*
     FLAG SECTION
     */
    
    //Go back to beginning of our input file
    rewind(infile);
    
    //Indicator of if we have passed the .data section and reached the .text section
    int passedData = 0;
    
    //Get each line of the MAL program and process them until we reach the end and find all identifiers
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
    
    /*This time we read each line of the file again for each identifier we previously found
     as we cycle through the file each time we search for the identifier on a line and if found
     we copy that line over to that identifier's next node pointer on the struct's linked list
     */
    //Marker for the first reference of any flow identifier in our program
    int firstReference = 0;
    int i = 0;
    for (i=0; i<flowCount; i++){
        //Go back to beginning of our input file
        rewind(infile);
        //Reset passedData
        passedData = 0;
        //Reset firstReference
        firstReference = 0;
        while (fgets(line, MAXLEN, infile) != NULL) {
            //Skip comments and whitespace lines
            if (line[0] == '#' || line [0] == '\n'){
                continue;
            }
            
            //Check if we've hit our first reference
            if (passedData==1){
                char *checking = strstr(line, ":");
                if (checking){
                    //Set our first reference variable to 1
                    firstReference = 1;
                }
            }
            
            //Skip lines containing : because we are done with finding the identifiers
            char *check = strstr(line, ":");
            if (check){
                continue;
            }
            //This is to check if the current line contains .text, if it does, we have passed the data section
            char *checkData = strstr(line, ".text");
            if (checkData){
                passedData = 1;
            }
            if (passedData == 0){
                continue;
            }
            
            if (firstReference == 0){
                continue;
            }
            //If we find a line in our input that contains the identifier, we copy that line to the
            //identifiers linked list
            char *foundID = strstr(line, flow[i].identifier);
            if (foundID){
                //create a node
                struct node *add = (struct node*) malloc(sizeof(struct node));
                strcpy(add->text, line);
                add->next = NULL;
                
                //If there is no lines on the list yet, make this line the head
                if (flow[i].head==NULL){
                    flow[i].head = add;
                }
                else{
                    struct node *current = flow[i].head;
                    while (current->next!=NULL){
                        current = current->next;
                    }
                    current->next=add;
                }
            }
        }
    }
    
    //Now we input all of our identifiers and their mentioned lines into our output file
    i = 0;
    for (i=0; i<flowCount; i++){
        //Add "Flow Control ID -Identifier-" into the file
        char tagged [100] = "Flow Control ID –";
        strcat(tagged,flow[i].identifier);
        strcat(tagged, "–\n");
        fputs(tagged, outfile);
        
        //Iterate through linked list for specific identifier and add lines to output file
        if (flow[i].head==NULL){
        }
        else{
            struct node *current = flow[i].head;
            fputs(flow[i].head->text,outfile);
            while (current->next!=NULL){
                current = current->next;
                fputs(current->text,outfile);
            }
        }
    }
    
    //Now that we are done, we can close both files
    fclose(infile);
    fclose(outfile);
    return 0;
}
