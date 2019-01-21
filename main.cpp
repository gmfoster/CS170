/* execvp: run a program */
/* Credits goes to Paul Krzyzanowski for providing an execve example in https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/index.html */

#include <stdlib.h>    /* needed to define exit() */
#include <unistd.h>    /* needed to define getpid() */
#include <stdio.h>    /* needed for printf() */
#include <string.h>
#include <iostream>
using namespace std;

char input[512];
char* arguments[512];
bool prompt = true;
bool amp = false;

void read();
int parse();
void command(char ** arguments, int arg_count);


int main(int argc, char **argv) {
    
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        prompt = false;
    }
    
    while(1) {
        read();
        int arg_count = parse();
        command(arguments, arg_count);
        
    }
}

void read() {
    if (prompt) {
        cout << "Shell: ";
    }
    fgets(input, 512, stdin);
    input[strlen(input)-1] = '\0';
    
}

int parse(){
    char* command = NULL;
    int argument_count = 0;
    char* token = strtok(input, "|");
    while(token) {
        printf("second token: %s\n", token);
        if(!command) command = token;
        printf("command: %s\n", command);
        arguments[argument_count] = token;
        argument_count++;
        token = strtok(NULL, "|");
        printf("next token: %s\n", token);
    }
    arguments[argument_count] = NULL;
    
    return argument_count;
}

void command(char ** arguments, int arg_count) {
    bool hasNext = false;
    bool hasPrev = false;
    
    for (int i = 0; i < arg_count; i ++){
        char oFile[512];
        char iFile[512];
        bool nextInput = false;
        bool nextOutput = false;
        bool setOfile = false;
        bool setIfile = false;
        int parseCount = 0;
        char * token  = strtok(arguments[i], " ");
        char ** parsedArg;
        
        while(token) {
            
            if (nextInput){
                //printf("Copying token to iFile \n");
                nextInput = false;
                strcpy(iFile, token);
                setIfile = true;
            }else if (nextOutput){
                //printf("Copying token to oFile \n");
                nextOutput = false;
                strcpy(oFile, token);
                setOfile = true;
            }else if (strcmp(token, ">") == 0){
                //printf("Found output token \n");
                nextOutput = true;
            }else if (strcmp(token, "<") == 0){
                //printf("Found input token \n");
                nextInput = true;
                
            }else{
                parsedArg[parseCount] = token;
                parseCount++;
            }
            
            token = strtok(NULL, " ");
        }
        parsedArg[parseCount] = NULL;
    }
}
