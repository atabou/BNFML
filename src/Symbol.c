#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

enum SymbolType {

    TERM,
    NONTERM

};

struct Symbol {

    unsigned int id;
    enum SymbolType type;
    union {
        struct { NonTerminal* nterm; };
        struct { Terminal* term; };
    };

};

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