#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct Binding {

    unsigned int id;
    NonTerminal* nterm;
    OrExpr* OrExpression; 

};


Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression ) {

    Binding* b = (Binding*) malloc(sizeof(Binding));

    b->id = idGenerator++;
    b->nterm = nterm;
    b->OrExpression = OrExpression;

    return b; 

}

void freeBinding(Binding* binding) {

    freeNonTerminal(binding->nterm);
    binding->nterm = NULL;

    freeOrExpr(binding->OrExpression);
    binding->OrExpression = NULL;

}

void printBinding( Binding* b ) {

    printNonTerminal( b->nterm );
    printf( " ::= " );
    printOrExpr( b->OrExpression );

}