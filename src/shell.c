#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "wrappers.h"

#define MAX_ARGS 100


/* HELPER FUNCTIONS */

/**
 * Clears the terminal screen by forking a child process and executing the clear command
 * 
 * @return      0 on success, -1 on failure
 */
int clear_helper() {
    int status;
    pid_t pid = Fork();
    
    if (pid == 0) {
        // in the child process
        char *args[] = {"clear", NULL};
        Execvp(args[0], NULL);
    } else {
        // parent process
        Waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Clear command exited with status %d\n", WEXITSTATUS(status));
            return -1;
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Clear command was terminated by signal %d\n", WTERMSIG(status));
            return -1;
        }
    }
    
    return 0;
}


/**
 * Executes a command entered by the user by forking a child process and using execvp to run the command.
 *
 * @param       args The array of command and arguments to execute
 * @return      0 on success, or a non-zero value on failure
 */
int execute(char *args[]) {
    int status;
    // create child process to execute the command
    pid_t pid = Fork();
    if (pid == 0) {
        // In child process
        Execvp(args[0], args); // Execute the command
    } else {
        Waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0) {
                fprintf(stderr, "[GenShell: program terminated abnormally][%d]\n", code);
            }
        } else if (WIFSIGNALED(status)) {
            // Killed by a signal — treat as abnormal, report the signal number
            fprintf(stderr, "[GenShell: program terminated abnormally][%d]\n", WTERMSIG(status));
        }
    }
    
    return 0;
}


/**
 * Helper function that prints the GenShell at the top of the terminal screen.
 * The first time this prints it will have a slight delay between printing lines.
 * A separate function exists to print it all other times
 */
void print_first_genshell() {
    FILE *fp = fopen("genshell.txt", "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        fputs(line, stdout);
        fflush(stdout);          // force the line out NOW
        usleep(50000);           // 50ms delay
    }

    fclose(fp);
}


/**
 * Helper function to print the GenShell at the top of the termina screen. 
 */
void print_genshell() {
    FILE *fp = fopen("genshell.txt", "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        fputs(line, stdout);
        fflush(stdout);          // force the line out NOW
    }

    fclose(fp);
}


/**
 * Inserts a space before every ';' in the input string so the tokenizer
 * treats it as its own token. Modifies input in place.
 *
 * @param input   the string to normalize (modified in place)
 * @param size    total size of the input buffer (for overflow safety)
 * @return        0 on success, -1 if the buffer is too small to hold the result
 */
int normalize_semicolons(char *input, size_t size) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ';') {
            size_t len = strlen(input);
            if (len + 1 >= size) {
                return -1;  // no room to shift
            }
            memmove(&input[i + 1], &input[i], len - i + 1);
            input[i] = ' ';
            i++;  // skip past the ';' we just shifted
        }
    }
    return 0;
}



/**
 * Helper function to tokenize the arguments taken in
 * 
 * @param input
 * @param args      the arguments to tokenize
 * @param max_args
 * @return          0 on success, -1 on failure
 */
int tokenize_arguments(char *input, char *args[], size_t max_args) {
    int i = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        if ((size_t)i >= max_args - 1) {
            return -1;                      // leave room for NULL
        }
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;                         // execvp requires this
    return i;
}



/* MAIN FUNCTIONS */

/**
 * Function to run the loop inside of the main method
 * TODO: implement this
 */
int shell_loop() {
    return 0;
}



int main(int argc, char *argv[]) {
    
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
    }
    
    int consecutive_enters = 0;     // counter for consecutive empty inputs
    char input[1024];               // command line input
    int run = 1;                    // condition to continue running the shell
    
    char *args[MAX_ARGS];                // Array to hold command and arguments
    
    // clears the terminal screen
    clear_helper();
    
    // prints GenShell in clean window
    print_first_genshell();
    
    while(run) {
        printf("GenShell> $ ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;          // EOF or error
        }
        
        // remove trailing newline
        input[strcspn(input, "\n")] = '\0';
        
        
        // prints the current working directory on double empty enter
        if (input[0] == '\0') {
            consecutive_enters++;
            if (consecutive_enters == 2) {
                char *pwd_args[] = {"pwd", NULL};       // Prepare the arguments for the pwd command
                execute(pwd_args);                      // Execute the pwd command
                consecutive_enters = 0;                 // Reset the counter
            }
            continue;                                   // Primpt again after executing pwd
        } else {
            consecutive_enters = 0;                     // Reset the counter if input is not empty
        }


        // normalize and tokenize input
        normalize_semicolons(input, sizeof(input));
        int n = tokenize_arguments(input, args, MAX_ARGS);
        
        // Check for exit
        if (strcmp(args[0], "exit") == 0) {
            run = 0;
            continue;
        }
        
        // check for clear command to clear the screen
        if (strcmp(args[0], "clear") == 0) {
            clear_helper();                             // Clear the terminal screen
            print_genshell();                           // Print the iShell banner after clearing the screen
            continue;
        } 
        
        
        // if arguments exist (which they should)
        if (n > 0) {
            execute(args);          // execute the command with provided arguments
        }
        
        
    }
    
    clear_helper();
    return 0;   
}
