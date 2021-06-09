
/**
 * 
 * @file Terminal.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Implementation file for the struct **Terminal** and its related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Terminal.h"
#include "Common.h"


/**
 * @struct **Terminal**
 * @brief struct to define a parsed **Terminal** value in BNFML
 * 
 */
struct Terminal {

    unsigned int id; /**< Global ID of the object. see: idGenerator*/
    char* value; /**< A regular expression representing the values a terminal can take.*/

}; 

/**
 * @brief Constructor to create a **Terminal** object.
 * 
 * @param value String in the form of a regular expression, representing the value of a **Terminal** object.
 * @return Terminal* Pointer to a newly created **Terminal** object.
 */
Terminal* new_Terminal( char* value ) {

    Terminal* t = (Terminal*) malloc(sizeof(Terminal));

    t->id = ParserID_Generator++;
    t->value = value;

    return t;

}

unsigned int getTerminal_id( Terminal* term ) {

    return term->id;

}

char* getTerminal_value( Terminal* term ) {

    return term->value;

}


/**
 * @brief Destructor for a **Terminal** object.
 * 
 * @param term A pointer to the terminal object you want to destruct.
 */
void freeTerminal( Terminal* term ) {

    free( term->value );
    term->value = NULL;

}

/**
 * @brief Prints a string representation of a **Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printTerminal( Terminal* term ) {

    printf( "'%s'", term->value );

}

/**
 * @brief Builds a graphviz representation of a **Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_Terminal( Terminal* term, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", term->id, term->value );

}