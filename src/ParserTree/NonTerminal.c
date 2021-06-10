/**
 * 
 * @file NonTerminal.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the NonTerminal struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/NonTerminal.h"
#include "Common.h"

void build_Graphviz_NonTerminal( void* this, FILE* fp );
void printNonTerminal( void* this );
void freeNonTerminal( void* this );
unsigned int getNonTerminal_id( void* this );

/**
 * @brief Constructor to create a **Non-Terminal** object.
 * 
 * @param name String that represents the name of a **Non-Terminal** object.
 * @return NonTerminal* Pointer to a newly created **Non-Terminal** object.
 */
NonTerminal* new_NonTerminal( char* name ) {

    NonTerminal* nt = (NonTerminal*) malloc(sizeof(NonTerminal));

    nt->id = ParserID_Generator++;
    nt->name = name;

    nt->fn = (CommonInterface*) malloc( sizeof(CommonInterface) );

    nt->fn->print = printNonTerminal;
    nt->fn->build_Graphviz = build_Graphviz_NonTerminal;
    nt->fn->destruct = freeNonTerminal;
    nt->fn->getID = getNonTerminal_id;

    return nt;

}

unsigned int getNonTerminal_id( void* this ) {

    NonTerminal* nterm = this;
    return nterm->id;

}

char* getNonTerminal_name( NonTerminal* nterm ) {
    return nterm->name;
}

/**
 * @brief Destructor for a **Non-Terminal** object.
 * 
 * @param term A pointer to the **Non-Terminal** object you want to destruct.
 */
void freeNonTerminal( void* this ) {

    NonTerminal* nterm = this;

    free(nterm->name);
    nterm->name = NULL;

    free( nterm->fn );
    nterm->fn = NULL;
    
}

/**
 * @brief Prints a string representation of a **Non-Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printNonTerminal( void* this ) {

    NonTerminal* nterm = this;
    printf( "%s", nterm->name );

}

/**
 * @brief Builds a graphviz representation of a **Non-Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_NonTerminal( void* this, FILE* fp ) {

    NonTerminal* nterm = this;
    fprintf( fp, "%u [label=\"%s\"];\n", nterm->id, nterm->name );

}