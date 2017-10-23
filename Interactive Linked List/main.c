/*
 This program is an interactive C program that prompts the user for commands, accepts said commands, and executes the commands. The program will continue to accept and process commands until the user types the end command.
 The program is an implementation of a linked list, with each node containing a string, a positive integer, and a pointer to the next node. No two nodes can have the same text.
 Commands Available:
 ina (Usage: ina num str) - inserts a new node, num represents a positive integer at which the new node will be inserted into the list after the node with that index (if there is no node at that index the new node will be inserted at the end of the list, str represents the text)
 inb (Usage: inb num str) - Same as ina except it inserts the new node into the position before the node specified for num, if no such node exists at the specified position, the new node will be inserted at the beginning of the list.
 del (Usage: del num) - Deletes the node at position num (only if a node exists at that position)
 rep (Usage: rep num str) - Replaces a node at position num with text str, if there is no node at position num, nothing changes in the list.
 prn (Usage: prn) - Prints the entire list (unless the list is empty) in the format of Index: Text with each node printed on its own line.
 end (Usage: end) - Stops the program entirely.
 */

//  Abraham Zakharov
//  Unix Login ID: ay451227
//  Lab Instructor: Areeb Khan
//  Lab: Friday @ 1:40PM - 2:35PM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//All of our functions
int ina (int num, char str[]);
int inb (int num, char str[]);
int del (int num);
int rep (int num, char str[]);
int prn (void);
int end (void);

/* Struct for each node in the linked list. */
struct node {
    int index;
    char text [255];
    struct node *next;
};

/* Our main method will constantly run until the 'end' command.
 */
int main(int argc, const char * argv[]) {
    while (1) {
        printf("Command? ");
        fflush(stdout);
        char cmd[4];
        int index;
        char in[255];
        char input[263];
        fgets(input, 263, stdin);
        sscanf (input, "%s %d %s", cmd, &index, in);
        if (strcmp(cmd, "ina") == 0){
            ina(index, in);
        }
        else if (strcmp(cmd, "inb") == 0){
            inb(index, in);
        }
        else if (strcmp(cmd, "del") == 0){
            del(index);
        }
        else if (strcmp(cmd, "rep") == 0){
            rep(index, in);
        }
        else if (strcmp(cmd, "prn") == 0){
            prn();
        }
        else if (strcmp(cmd, "end") == 0){
            end();
        }
    }
    return 0;
}

//Function to insert a node after the specified node at index num
int ina (int num, char str[]){
    printf("ina: %d %s\n", num, str);
    return 0;
}

//Function to insert a node before the specified node at index num
int inb (int num, char str[]){
    printf("inb: %d %s\n", num, str);
    return 0;
}

//Function to delete a node at the specified index
int del (int num){
    printf("del: %d \n", num);
    return 0;
}

//Function to replace the node at the specified index
int rep (int num, char str[]){
    printf("rep: %d %s\n", num, str);
    return 0;
}

//Function to print the list
int prn (){
    printf("prn\n");
    return 0;
}

//Function to end the program
int end (){
    printf("end\n");
    exit(0);
    return 0;
}
