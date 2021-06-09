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

#include "NonTerminal.h"
#include "Common.h"

struct NonTerminal {

    unsigned int id; /**< Global ID of the object. see: idGenerator*/
    char* name; /**< A string representing the name of a non-terminal.*/

}; 

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

    return nt;

}

int getNonTerminal_id( NonTerminal* nterm ) {
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
void freeNonTerminal( NonTerminal* nterm ) {

    free(nterm->name);
    nterm->name = NULL;
    
}

/**
 * @brief Prints a string representation of a **Non-Terminal** object.
 * 
 * @param term A pointer to the **Terminal** object you want to print.
 */
void printNonTerminal( NonTerminal* nterm ) {

    printf( "%s", nterm->name );

}

/**
 * @brief Builds a graphviz representation of a **Non-Terminal** object and prints it to a file.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_NonTerminal( NonTerminal* nterm, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", nterm->id, nterm->name );

}