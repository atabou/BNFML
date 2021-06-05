
#ifndef EXPR

    #define EXPR

    #include "BNF.h"

    typedef struct Symbol Symbol;
    Symbol* createNonTerminalSymbol( NonTerminal* nterm );
    Symbol* createTerminalSymbol( Terminal* term );


#endif