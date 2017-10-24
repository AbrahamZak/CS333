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

//Function to check if there exists a node with the same string we are trying to insert
int check (char str[]);
//Updates the index numbers to reflect actual position on the list
int reorder (void);

/* Struct for each node in the linked list. */
struct node {
    int index;
    char text [255];
    struct node *next;
};

//Our head node
struct node *head = NULL;

//The size of our linked list
int size = 0;

/* Our main method will constantly run until the 'end' command.
 */
int main(int argc, const char * argv[]) {
    //This node is our head
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
    //If this is the first node insert it at the head
    if (size==0){
        //create a begin node
        struct node *begin = (struct node*) malloc(sizeof(struct node));
        
        begin->index = 1;
        strcpy(begin->text, str);
        
        //point it to the head
        begin->next = head;
        
        //point the head to begin
        head = begin;
        
        //Increment size
        size++;
        
        printf("Text inserted at the beginning\n");
        fflush(stdout);
        
        return 0;
    }
    
    //Check if the string is already in our list
    if (check(str)==1){
        printf("Such text exists already\n");
        fflush(stdout);
        return 0;
    }
    
    //If the index provided is greater than the length of the list, insert the node at the end
    else if (num>size){
        int i = 1;
        struct node *ptr = head;
        //Traverse the list to the end
        while(i!=size) {
            ptr = ptr->next;
            i++;
        }
        
        //Make a node with data
        struct node *insert = (struct node*) malloc(sizeof(struct node));
        insert->index = size + 1;
        strcpy(insert->text, str);
        
        //Add the node
        ptr->next=insert;
        
        //Increment size
        size++;
        
        printf("Text inserted at the end\n");
        fflush(stdout);
    }
    //If the index provided is within range we insert the new node after that index
    else{
        //Make a node with data
        struct node *insert = (struct node*) malloc(sizeof(struct node));
        insert->index = num+1;
        strcpy(insert->text, str);
        
        //Traverse the list
        struct node *ptr = head;
        int i=1;
        while (i<num){
            ptr = ptr->next;
            i++;
        }
        //Make a node for the next element
        struct node *postptr = ptr->next;
        
        /*Make our index->next point to the node we are inserting
         Then make insert->next point to the node that originally went after
         */
        ptr->next = insert;
        insert->next = postptr;
        
        //Increment size
        size++;
        
        //Reorder our index numbers across the list
        reorder();
        
        printf("Ok\n");
        fflush(stdout);
    }
    return 0;
}

//Function to insert a node before the specified node at index num
int inb (int num, char str[]){
    //If this is the first node insert it at the head
    if (size==0){
        //create a begin node
        struct node *begin = (struct node*) malloc(sizeof(struct node));
        
        begin->index = 1;
        strcpy(begin->text, str);
        
        //point it to the head
        begin->next = head;
        
        //point the head to begin
        head = begin;
        
        //Increment size
        size++;
        
        printf("Text inserted at the beginning\n");
        fflush(stdout);
        
        return 0;
    }
    
    //Check if the string is already in our list
    if (check(str)==1){
        printf("Such text exists already\n");
        fflush(stdout);
        return 0;
    }
    
    //If the index provided is greater than the length of the list, insert the node at the beginning
    else if (num>size){
        
        //Make a node with data
        struct node *insert = (struct node*) malloc(sizeof(struct node));
        insert->index = 1;
        strcpy(insert->text, str);
        
        //point next to the old head
        insert->next = head;
        
        //point the head to this node
        head = insert;
        
        //Increment size
        size++;
        
        //Reorder our index numbers across the list
        reorder();
        
        printf("Text inserted at the beginning\n");
        fflush(stdout);
    }
    //If the index provided is within range we insert the new node before that index
    else{
        //Make a node with data
        struct node *insert = (struct node*) malloc(sizeof(struct node));
        insert->index = num-1;
        strcpy(insert->text, str);
        
        //Traverse the list to reach the element before our index
        struct node *preptr = head;
        int i=1;
        while (i<num-1){
            preptr = preptr->next;
            i++;
        }
        
        //Make a node for the next element, the index
        struct node *ptr = preptr->next;
        
        /*Make our preindex->next point to the node we are inserting
         Then make insert->next point to the index
         */
        preptr->next = insert;
        insert->next = ptr;
        
        //Increment size
        size++;
        
        //Reorder our index numbers across the list
        reorder();
        
        printf("Ok\n");
        fflush(stdout);
    }
    return 0;
}

//Function to delete a node at the specified index
int del (int num){
    //If the replacement index is not on the list, tell user there is no such index
    if (num>size){
        printf("No such index\n");
        fflush(stdout);
        return 0;
    }
    else{
        //Traverse the list to reach the element before our index
        struct node *preptr = head;
        int i=1;
        while (i<num-1){
            preptr = preptr->next;
            i++;
        }
        //If there is an element after our index we put it in postptr
        if (preptr->next->next!=NULL){
        struct node *postptr = preptr->next->next;
            //Delete the element by setting the pre->next to the post
            preptr->next = postptr;
        }
        //If there is no element after the index, we set preptr->next to NULL
        preptr->next = NULL;
        
        //Decrement size
        size--;
        
        //Reorder our index numbers across the list
        reorder();
        
        printf("Deleted\n");
        fflush(stdout);
    }
    return 0;
}

//Function to replace the node at the specified index
int rep (int num, char str[]){
    //If the replacement index is not on the list, tell user there is no such index
    if (num>size){
        printf("No such index\n");
        fflush(stdout);
        return 0;
    }
    //Otherwise traverse the list until we reach the desired index
    else{
        struct node *ptr = head;
        int i=1;
        while (i<num){
            ptr = ptr->next;
            i++;
        }
        //Replace the text at the index with the new text
        strcpy(ptr->text, str);
        printf("Replaced\n");
        fflush(stdout);
    }
    return 0;
}

//Function to print the list
int prn (){
    if (size==0){
        printf("The list is empty\n");
        fflush(stdout);
    }
    
    struct node *ptr = head;
    int i = 1;
    //start from the beginning and traverse the list unril reaching hitting a NULL node (the end)
    while(i!=size+1) {
        printf("%d: %s\n",ptr->index,ptr->text);
        fflush(stdout);
        ptr = ptr->next;
        i++;
    }
    return 0;
}

//Updates the index numbers to reflect actual position on the list
int reorder(){
    int i = 1;
    struct node *ptr = head;
    //Traverse the list to the end
    while(i!=size+1) {
        ptr->index = i;
        i++;
        ptr = ptr->next;
    }
    return 0;
}

//Function to check if there exists a node with the same string we are trying to insert
int check (char str[]){
    int i = 1;
    struct node *ptr = head;
    //Traverse the list to the end
    while(i!=size+1) {
        //If there is a match we return 1
        if (strcmp(str, ptr->text) == 0){
            return 1;
        }
        ptr = ptr->next;
        i++;
    }
    //Otherwise we return 0
    return 0;
}

//Function to end the program
int end (){
    exit(0);
    return 0;
}
