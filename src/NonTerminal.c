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

#include "ParserTree.h"

/**
 * @brief Constructor to create a **Non-Terminal** object.
 * 
 * @param Name String that represents the name of a **Non-Terminal** object.
 * @return NonTerminal* Pointer to a newly created **Non-Terminal** object.
 */
NonTerminal* createNonTerminal( char* Name ) {

    NonTerminal* nt = (NonTerminal*) malloc(sizeof(NonTerminal));

    nt->id = idGenerator++;
    nt->Name = Name;

    return nt;

}

/**
 * @brief Destructor for a **Non-Terminal** object.
 * 
 * @param term A pointer to the **Non-Terminal** object you want to destruct.
 */
void freeNonTerminal( NonTerminal* nterm ) {

    free(nterm->Name);
    nterm->Name = NULL;
    
}

/**
 * @brief Prints a string representation of a **Non-Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printNonTerminal( NonTerminal* nterm ) {

    printf( "%s", nterm->Name );

}

/**
 * @brief Builds a graphviz representation of a **Non-Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void buildNonTerminalNode( NonTerminal* nterm, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", nterm->id, nterm->Name );

}