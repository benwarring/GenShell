#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "wrappers.h"




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
 * Helper function that prints the GenShell at the top of the terminal screen
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
        usleep(50000);           // 50ms delay
    }

    fclose(fp);
}



int main(int argc, char *argv[]) {
    
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
    }
    
    int consecutive_enters = 0;     // counter for consecutive empty inputs
    char input[1024];
    int run = 1;                    // condition to continue running the shell
    
    // clears the terminal screen
    clear_helper();
    
    // prints GenShell in clean window
    print_genshell();
    
 
    return 0;   
}
