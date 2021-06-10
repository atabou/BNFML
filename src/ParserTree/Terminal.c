
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

#include "ParserTree/Terminal.h"
#include "Common.h" 

void build_Graphviz_Terminal( void* this, FILE* fp );
void printTerminal( void* this );
void freeTerminal( void* this );
unsigned int getTerminal_id( void* this );

/**
 * @brief Constructor to create a **Terminal** object.
 * 
 * @param value String in the form of a regular expression, representing the value of a **Terminal** object.
 * @return Terminal* Pointer to a newly created **Terminal** object.
 */
Terminal* new_Terminal( char* value ) {

    printf( "Creating a Terminal expression.\n" );

    Terminal* t = (Terminal*) malloc(sizeof(Terminal));

    t->id = ParserID_Generator++;
    t->value = value;

    t->fn = (CommonInterface*) malloc( sizeof(CommonInterface) );

    t->fn->print = printTerminal;
    t->fn->build_Graphviz = build_Graphviz_Terminal;
    t->fn->destruct = freeTerminal;
    t->fn->getID = getTerminal_id;

    printf( "[SUCCESS] Finished creating a Terminal expression.\n" );

    return t;

}

unsigned int getTerminal_id( void* this ) {

    Terminal* term = this;
    printf( "Terminal ID:\n");
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
void freeTerminal( void* this ) {

    Terminal* term = this;
    printf( "Terminal ID: %d\n", term->id);
    
    free( term->value );
    term->value = NULL;

    free( term->fn );
    term->fn = NULL;
    

}

/**
 * @brief Prints a string representation of a **Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printTerminal( void* this ) {

    Terminal* term = this;
    printf( "Pint Terminal:\n");
    printf( "'%s'", term->value );

}

/**
 * @brief Builds a graphviz representation of a **Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_Terminal( void* this, FILE* fp ) {

    Terminal* term = this;
    printf( "Graphiz Terminal:\n");
    fprintf( fp, "%u [label=\"%s\"];\n", term->id, term->value );

}