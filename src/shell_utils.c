#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#include "wrappers.h"


/* HELPER FUNCTIONS */

/**
 * Clears the terminal screen by forking a child process and executing the clear command
 * 
 * @return      0 on success, -1 on failure
 */
int clear_helper(void) {
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
 * Helper function that prints the GenShell at the top of the terminal screen.
 * The first time this prints it will have a slight delay between printing lines.
 * A separate function exists to print it all other times
 */
void print_first_genshell(void) {
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
void print_genshell(void) {
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