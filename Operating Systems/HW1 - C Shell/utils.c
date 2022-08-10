/*
    utils.c -- Various useful shell utility functions.

    Copyright (C) 2016, 2021 Lawrence Sebald
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
    UMBC CMSC 421
    Spring 2021
    Project 1

    Due Date: 2/28/21 11:59:00 pm
	//
    Author Name:
    Author email:
    Description: a simple linux shell designed to perform basic linux commands
*/

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#include "utils.h"

size_t count_spaces(const char *str) {
    size_t rv = 0;
/*
    In this project, you are going to implement a number of functions to
    create a simple linux shell interface to perform basic linux commands.
    Please note that the below set of functions may be modified as you see fit.
    We are just giving the following as a suggestion. If you do use our
    suggested design, you *will* need to modify the function signatures (adding
    arguments and return types).
*/

    while(*str) {
        if(isspace(*str++))
            ++rv;
/*
DEFINE FUNCTION PROTOTYPES (add arguments/return types as needed)
void user_prompt_loop()
char* get_user_command()
void parse_command(char TwoDadrress[][], char* Rawstring)
void execute_command()
*/

        int main(int argc, char *argv[]) {
            /*
                Write the main function that checks the number of arguments passed to
                ensure no command-line arguments are passed; that is to say that if the
                number of arguments is greater than 1 then exit the shell with a message
                to stderr and return value of 1. Otherwise call the user_prompt_loop()
                function to get user input repeatedly until the user enters the "exit"
                command.
            */

            if (argc > 1){
                fprintf(stderr, "More than 1 arguement passed\n");
                return 1;
            }
            else {
                user_prompt_loop();
            }

            return rv;
            return 0;
        }

        void flush_input(FILE *fp) {
            int c;
/*
    user_prompt_loop():
    Get the user input using a loop until the user exits, prompting the user for
    a command. Gets command and sends it to a parser, then compares the first
    element to the two built-in commands ("proc", and "exit"). If it's none of
    the built-in commands, send it to the execute_command() function. If the
    user decides to exit, then exit 0 or exit with the user given value.
*/
            void user_prompt_loop() {
                /*
                  loop:
                    1. prompt the user to type command by printing "$ " (don't forget the
                       space)
                       */
                printf("In user_prompt_loop");
                printf("\n$ ");


                //2. get the user input using get_user_command() function
                char *ptrUserCommand = get_user_command();

                // Test code to see if get_user_command works
                printf("You typed: %s\n", ptrUserCommand);




                /*
                3. parse the user input using parse_command() function
                Example:
                    user input: "ls -la"
                    parsed output: ["ls", "-la", NULL]

                */
                //DECLARE 2d char array that can hold words "ls" "-la" "things"
                // first d, holds number of words, 25
                // second d, holds numbers of chars, 100 per word
                char splicedString[25][100];

                // Clear Array
                memset(splicedString,0,sizeof(splicedString));


                // Declare a char_ptr to point to the first element to a 2d array
                //char *splicedStringAddressPTR = splicedString;


                //PASS TO PARSE COMMAND, passing first address of splicedString, and userInput
                parse_command(splicedString, ptrUserCommand);






                /*
                4. compare the first element of the parsed output to "proc"and "exit"
                5. if the first element is "proc" then you have to use the /proc file
                   system as described in part 2 of the project
                    i) concat the full command:
                        Ex: user input $ proc /process_id_no/status
                            concated output: /proc/process_id_no/status
                    ii) read from the file line by line. you may user fopen() and
                        getline() functions
                    iii) display the following information according to the user input
                         from /proc
                        a) Get the cpu information if the input is /proc/cpuinfo
                        - Cpu Mhz
                        - Cache size
                        - Cpu cores
                        - Address sizes
                        b) Get the number of currently running processes from
                           /proc/loadavg
                        c) Get how many seconds your box has been up, and how many
                           seconds it has been idle from /proc/uptime
                        d) Get the following information from /proc/process_id_no/status
                        - the vm size of the virtual memory allocated the vbox
                        - the most memory used vmpeak
                        - the process state
                        - the parent pid
                        - the number of threads
                        - number of voluntary context switches
                        - number of involuntary context switches
                        e) display the list of environment variables from
                           /proc/process_id_no/environ
                        f) display the performance information if the user input is
                           /proc/process_id_no/sched



                6. if the first element is "exit" the use the exit() function to
                   terminate the program
                   */
                if (splicedString[0][0] == "exit"){

                    exit(0);
                }


                /* Read until we get an EOF character or a newline. */
                while(1) {
                    c = fgetc(fp);

                    if(c == '\n' || c == EOF)
                        return;
                }
                //7. otherwise pass the parsed command to execute_command() function





                //8. free the allocated memory using the free() function
                // ptrUserCommand was allocated memory, by GetUserCommand
                free(ptrUserCommand);

                /*
                    Functions you may find useful here (not an exhaustive list):
                    get_user_command(), parse_command(), execute_command(), strcmp(),
                    strcat(), strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(),
                    atoi(), fgetc()
                */

                // Free ptrUserCommand for next use
                free(ptrUserCommand);
            }

            char *unescape(const char *str, FILE *errf) {
                size_t len = strlen(str);
                char *unesc, *rv;
                char cur;
                char quoted = 0;

                /* Allocate space for the new string. Since only potentially removing
                   characters, it will be no larger than the original string... */
                if(!(rv = (char *)malloc(len + 1))) {
                    fprintf(errf, "shell error: %s\n", strerror(errno));
                    return NULL;
                }
/*
    get_user_command():
    Take input of arbitrary size from the user and return to the
    user_prompt_loop()

    unesc = rv;

    /* Scan through the string... */
                while(*str) {
                    cur = *str++;

                    /* Is this the beginning of an escape sequence? */
                    if(!quoted && cur == '\\') {
                        cur = *str++;

                        switch(cur) {
                            case '\0':
                                fprintf(errf, "shell error: illegal escape sequence\n");
                                free(rv);
                                return NULL;

                            case 'n':
                                *unesc++ = '\n';
                                continue;
                            case 'a':
                                *unesc++ = '\a';
                                continue;
                            case 'b':
                                *unesc++ = '\b';
                                continue;
                            case 'r':
                                *unesc++ = '\r';
                                continue;
                            case '\\':
                                *unesc++ = '\\';
                                continue;
                            case 'f':
                                *unesc++ = '\f';
                                continue;
                            case 'v':
                                *unesc++ = '\v';
                                continue;
                            case '\'':
                                *unesc++ = '\'';
                                continue;
                            case '"':
                                *unesc++ = '"';
                                continue;
                            case '?':
                                *unesc++ = '?';
                                continue;
                            case '*':
                                *unesc++ = '*';
                                continue;
                            case '$':
                                *unesc++ = '$';
                                continue;
                            case 't':
                                *unesc++ = '\t';
                                continue;
                            case ' ':
                                *unesc++ = ' ';
                                continue;
                            case '!':
                                *unesc++ = '!';
                                continue;

                                /* Ugh... Octal. */
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            {
                                int tmp = (cur - '0') << 6;

                                cur = *str++;
                                if(cur < '0' || cur > '7') {
                                    free(rv);
                                    return NULL;
                                }

                                tmp |= (cur - '0') << 3;

                                cur = *str++;
                                if(cur < '0' || cur > '7') {
                                    free(rv);
                                    return NULL;
                                }

                                tmp |= (cur - '0');
                                *unesc++ = (char)tmp;
                                continue;
                            }

                                /* And, for more fun, hex! */
                            case 'x':
                            case 'X':
                            {
                                int tmp;

                                cur = *str++;
                                if(cur >= '0' && cur <= '9')
                                    tmp = (cur - '0') << 4;
                                else if(cur >= 'a' && cur <= 'f')
                                    tmp = (cur - 'a' + 10) << 4;
                                else if(cur >= 'A' && cur <= 'F')
                                    tmp = (cur - 'A' + 10) << 4;
                                else {
                                    free(rv);
                                    return NULL;
                                }

                                cur = *str++;
                                if(cur >= '0' && cur <= '9')
                                    tmp |= (cur - '0');
                                else if(cur >= 'a' && cur <= 'f')
                                    tmp |= (cur - 'a' + 10);
                                else if(cur >= 'A' && cur <= 'F')
                                    tmp |= (cur - 'A' + 10);
                                else {
                                    free(rv);
                                    return NULL;
                                }

                                *unesc++ = (char)tmp;
                                continue;
                            }

                            default:
                                *unesc++ = cur;
                        }

                        continue;
                    }
                        /* Escape sequences in quoted strings are very limited... */
                    else if(quoted && cur == '\\') {
                        cur = *str++;

                        if(!cur) {
                            fprintf(errf, "shell error: invalid escape sequence\n");
                            free(rv);
                            return NULL;
                        }

                        if(cur != quoted)
                            *unesc++ = '\\';
                    }
                        /* Is this the beginning of a quoted string? */
                    else if(!quoted && (cur == '\'' || cur == '"')) {
                        quoted = cur;
                        continue;
                    }
                    else if(quoted && cur == quoted) {
                        quoted = 0;
                        continue;
                    }
                    Returns: a Char pointer
                    */
                    char* get_user_command() {
                        /*
                            Functions you may find useful (not an exhaustive list):
                            malloc(), realloc(), getline(), fgetc()
                        */

                        /* If we get here, it's not part of an escape, so copy it directly. */
                        *unesc++ = cur;
                    }
                    // Unsigned int
                    size_t bufferSize = 2500;

                    /* Did we terminate any quotes that we started? */
                    if(quoted) {
                        fprintf(errf, "shell error: unterminated quote\n");
                        free(rv);
                        return NULL;
                    }
                    // ON THE HEAP
                    // Allocates 2500 characters to string
                    char *string = (char*)malloc(sizeof(char)*bufferSize);

                    // Error if "string" ptr is not pointing to an address
                    if (string == NULL){
                        printf("get_user_command, error, string was not malloc properly");
                    }

                    // While "int" gets number of characters, string should be populated with userinput
                    int numberOfCharactersRead = getline(&string, &bufferSize, stdin);


                    // Return pointer of "string"
                    return string;

                    *unesc = 0;

                    return rv;
                }

                int first_unquoted_space(const char *str) {
                    int pos = 0;
                    const char *tmp = str;
                    char quoted = 0, last = 0, cur = 0;

                    while(*tmp) {
                        last = cur;
                        cur = *tmp;

                        if(last != '\\') {
                            if(!quoted && (cur == '\'' || cur == '"'))
                                quoted = cur;
                            else if(quoted && cur == quoted)
                                quoted = 0;
                            if(!quoted && isspace(cur))
                                return pos;
                        }

                        ++pos;
                        ++tmp;

/*
    parse_command():
    Take command input read from the user and parse appropriately.
    Example:
        user input: "ls -la"
        parsed output: ["ls", "-la", NULL]
    Example:
        user input: "echo     hello                     world  "
        parsed output: ["echo", "hello", "world", NULL]
*/
                        void parse_command(char TwoDadrress[][], char* Rawstring) {
                            /*
                                Functions you may find useful (not an exhaustive list):
                                malloc(), realloc(), free(), strlen(), first_unquoted_space(),
                                unescape()
                            */

                            printf("Inside parse_Command\n");

                            // Unescape RawString, Unsescape should return a pointer
                            char *NewRawstring = unescape(Rawstring, stderr);

                            if (NewRawstring == NULL){
                                printf("Inside parse_command, problem with Unescape, returned NULL");
                            }

                            printf("Test Code: Inside Parse_command, NewRawString is: %s\n", NewRawstring);




                            // Token splitting
                            char *token;
                            char *restOfCharacters = NewRawstring;
                            int i = 0;

                            printf("Trying to token split\n");
                            while ((token = strtok_r(restOfCharacters, " ", &restOfCharacters))){
                                printf("%s\n",token);
                                TwoDadrress[i] = token;
                            }
                            printf("Out of token split\n");

                            return -1;

                            // Last step is to free() Pointer returned by UneScape
                            free(NewRawstring);

                        }

/*
    execute_command():
    Execute the parsed command if the commands are neither proc nor exit;
    fork a process and execute the parsed command inside the child process
*/
                        void execute_command() {
                            /*
                                Functions you may find useful (not an exhaustive list):
                                fork(), execvp(), waitpid(), wait()
                            */
                        }