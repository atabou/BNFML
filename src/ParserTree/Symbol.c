
#include "ParserTree/Symbol.h"
#include <stdlib.h>


enum SymbolType getSymbol_type( Symbol* this );
Terminal* getSymbol_term( Symbol* this );
NonTerminal* getSymbol_nterm( Symbol* this );



Symbol* new_Symbol_Terminal( Terminal* term ) {

    printf( "Creating new Terminal symbol.\n" );

    Symbol* s = (Symbol*) malloc( sizeof( Symbol ) );

    s->type = TERMINAL_SYMBOL;
    s->term = term;

    s->getType = getSymbol_type;
    s->getTerminal = getSymbol_term;

    printf( "[Success] Finished creating Terminal symbol.\n" );

    return s;

}

Symbol* new_Symbol_NonTerminal( NonTerminal* nterm ) {

    printf( "Creating new Terminal symbol.\n" );

    Symbol* s = (Symbol*) malloc( sizeof( Symbol ) );

    s->type = NON_TERMINAL_SYMBOL;
    s->nterm = nterm;

    s->getType = getSymbol_type;
    s->getNonTerminal = getSymbol_nterm;

    printf( "[Success] Finished creating Terminal symbol.\n" );

    return s;

}

enum SymbolType getSymbol_type( Symbol* this ) {

    return this->type;

}

Terminal* getSymbol_term( Symbol* this ) {

    return this->term;

}

NonTerminal* getSymbol_nterm( Symbol* this ) {

    return this->nterm;

}