@@ -45,6 +45,14 @@ int main(int argc, char *argv[]) {
    command.
    */

    if (argc > 1){
        printf(stderr, "More than 1 arguement passed\n");
        return 1;
    }
    else {
        user_prompt_loop();
    }

    return 0;
}

@ -56,16 +64,54 @@ int main(int argc, char *argv[]) {
    the built-in commands, send it to the execute_command() function. If the
    user decides to exit, then exit 0 or exit with the user given value.
                                                                  */
                                                                  user_prompt_loop() {
        void user_prompt_loop() {
            /*
              loop:
                1. prompt the user to type command by printing "$ " (don't forget the
                   space)
                2. get the user input using get_user_command() function
                   */
            printf("In user_prompt_loop");
            printf("\n$ ");


            //2. get the user input using get_user_command() function
            char ptrUserCommand* = get_user_command();

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
    @ -97,11 +143,28 @@ user_prompt_loop() {
                       /proc/process_id_no/environ
                    f) display the performance information if the user input is
                       /proc/process_id_no/sched



            6. if the first element is "exit" the use the exit() function to
               terminate the program
            7. otherwise pass the parsed command to execute_command() function
            8. free the allocated memory using the free() function
        */
            */
            if (splicedString[0][0] == "exit"){

                exit 0;
            }



            //7. otherwise pass the parsed command to execute_command() function




            */
            //8. free the allocated memory using the free() function
            // ptrUserCommand was allocated memory, by GetUserCommand
            free(ptrUserCommand);

            /*
                Functions you may find useful here (not an exhaustive list):
        @ -109,20 +172,48 @@ user_prompt_loop() {
                strcat(), strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(),
                atoi(), fgetc()
            */

            // Free ptrUserCommand for next use
            free(ptrUserCommand);
        }

/*
    get_user_command():
    Take input of arbitrary size from the user and return to the
    user_prompt_loop()

    Returns: a Char pointer
*/
        get_user_command() {
            char* get_user_command() {
                /*
                    Functions you may find useful (not an exhaustive list):
                    malloc(), realloc(), getline(), fgetc()
                */

                // Unsigned int
                size_t bufferSize = 2500;

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


            }



/*
    parse_command():
    Take command input read from the user and parse appropriately.
@ -133,12 +224,43 @@ get_user_command() {
        user input: "echo     hello                     world  "
        parsed output: ["echo", "hello", "world", NULL]
*/
            parse_command() {
                void parse_command(char TwoDadrress[][], char* Rawstring) {
                    /*
                        Functions you may find useful (not an exhaustive list):
                        malloc(), realloc(), free(), strlen(), first_unquoted_space(),
                        unescape()
                    */

                    printf("Inside parse_Command\n");

                    // Unescape RawString, Unsescape should return a pointer
                    char *NewRawstring = Unescape(Rawstring, stderr);

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
                    printf("Out of token split\n")


                    // Last step is to free() Pointer returned by UneScape
                    free(NewRawstring);

                }

/*
@ -146,7 +268,7 @@ parse_command() {
    Execute the parsed command if the commands are neither proc nor exit;
    fork a process and execute the parsed command inside the child process
*/
                execute_command() {
                    void execute_command() {
                        /*
                            Functions you may find useful (not an exhaustive list):
                            fork(), execvp(), waitpid(), wait()
                    @ @@