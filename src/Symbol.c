#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"



Symbol* createNonTerminalSymbol( NonTerminal* nterm ) {

    Symbol* e = (Symbol*) malloc(sizeof(Symbol));

    e->id = idGenerator++;
    e->type = NONTERM;
    e->nterm = nterm;

    return e;

}

Symbol* createTerminalSymbol( Terminal* term ) {

    Symbol* e = (Symbol*) malloc(sizeof(Symbol));

    e->id = idGenerator++;
    e->type = TERM;
    e->term = term;

    return e;

}

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

void printSymbol( Symbol* symbol ) {

    if( symbol->type == TERM ) {

        printTerminal( symbol->term );

    } else {

        printNonTerminal( symbol->nterm );

    }

}

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