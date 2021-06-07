/**
 * 
 * @file Symbol.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the Symbol struct related functions
 * @bug No known bugs.
 */


#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"


/**
 * @brief Constructor to create a **Symbol** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @return Symbol* A Pointer to a newly created **Symbol** object.
 */
Symbol* createNonTerminalSymbol( NonTerminal* nterm ) {

    Symbol* e = (Symbol*) malloc(sizeof(Symbol));

    e->id = idGenerator++;
    e->type = NONTERM;
    e->nterm = nterm;

    return e;

}

/**
 * @brief Constructor to create a **Symbol** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @return Symbol* A Pointer to a newly created **Symbol** object.
 */
Symbol* createTerminalSymbol( Terminal* term ) {

    Symbol* e = (Symbol*) malloc(sizeof(Symbol));

    e->id = idGenerator++;
    e->type = TERM;
    e->term = term;

    return e;

}

/**
 * @brief Destructor for a **Symbol** object.
 * 
 * @param symbol A pointer to the **Symbol** object you want to destruct.
 */
void freeSymbol(Symbol* symbol) {

    if( symbol->type == TERM ) {

        freeTerminal( symbol->term );
        free( symbol->term );
        symbol->term = NULL;

    } else {

        freeNonTerminal( symbol->nterm );
        free( symbol->nterm );
        symbol->nterm = NULL;

    }

}

/**
 * @brief Prints a string representation of a **Symbol** object.
 * 
 * @param symbol A pointer to the **Symbol** object you want to print.
 */
void printSymbol( Symbol* symbol ) {

    if( symbol->type == TERM ) {

        printTerminal( symbol->term );

    } else {

        printNonTerminal( symbol->nterm );

    }

}

/**
 * @brief Builds a graphviz representation of a **Symbol** object and prints it to a file.
 * 
 * @param symbol A pointer to a **Symbol** object.
 * @param fp A valid file pointer.
 */
void buildSymbolNode( Symbol* symbol, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", symbol->id, "symbol" );

    if( symbol->type == TERM ) {

        fprintf( fp, "%u -> %u [label=\"Terminal\"];\n", symbol->id, symbol->term->id );
        buildTerminalNode( symbol->term, fp );

    } else {

        fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", symbol->id, symbol->nterm->id );
        buildNonTerminalNode( symbol->nterm, fp );

    }

}