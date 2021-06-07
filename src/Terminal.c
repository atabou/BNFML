
/**
 * 
 * @file Terminal.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"

/**
 * @brief Constructor to create a **Terminal** object.
 * 
 * @param Regex String in the form of a regular expression, representing the value of a **Terminal** object.
 * @return Terminal* Pointer to a newly created **Terminal** object.
 */
Terminal* createTerminal( char* Regex ) {

    Terminal* t = (Terminal*) malloc(sizeof(Terminal));

    t->id = idGenerator++;
    t->regex = Regex;

    return t;

}

/**
 * @brief Destructor for a **Terminal** object.
 * 
 * @param term A pointer to the terminal object you want to destruct.
 */
void freeTerminal( Terminal* term ) {

    free( term->regex );
    term->regex = NULL;

}

/**
 * @brief Prints a string representation of a **Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printTerminal( Terminal* term ) {

    printf( "'%s'", term->regex );

}

/**
 * @brief Builds a graphviz representation of a **Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void buildTerminalNode( Terminal* term, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", term->id, term->regex );

}