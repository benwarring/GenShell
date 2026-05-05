/**
 * Clears the terminal screen by forking a child process and executing the clear command
 * 
 * @return      0 on success, -1 on failure
 */
int clear_helper(void);



/**
 * Helper function that prints the GenShell at the top of the terminal screen.
 * The first time this prints it will have a slight delay between printing lines.
 * A separate function exists to print it all other times
 */
void print_first_genshell(void);



/**
 * Helper function to print the GenShell at the top of the termina screen. 
 */
void print_genshell(void);