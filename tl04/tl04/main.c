/**
 * @file main.c
 * @author YOUR TAs!
 * @date 2020-11-16
 *
 * DO NOT MODIFY THIS FILE.
 */
#include "tl04.h"

/**
 * @brief Main function, responsible for parsing command line arguments
 *
 * Note: This function/file is provided as the entry point of the program.
 * All it does is to call your my_main function in tl04.c with the command line arguments.
 *
 * In any C program, there would be only one true "main" function, however,
 * this is due to the way the local autograder is setup.
 *
 * Run "make tl04" to get the tl04 object file and then run the program like:
 * ./tl04 "x:120 y:50" "r:12 g:17 b:8" "r:5 g:0 b:25"
 *
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int main(int argc, char const *argv[])
{
    return my_main(argc, argv);
}