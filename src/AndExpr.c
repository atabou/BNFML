
#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct AndExpr {

    unsigned int id;
    AndExpr* prevAndExpr;
    Symbol* symbol;

};

AndExpr* createAndExpr( Symbol* symbol ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = NULL;
    a->symbol = symbol;

    return a;

}


AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = lst;
    a->symbol = symbol;

    return a;

}

void freeAndExpr(AndExpr* AndExpression) {

    freeSymbol( AndExpression->symbol );
    free( AndExpression->symbol );
    AndExpression->symbol = NULL;

    if( AndExpression->prevAndExpr != NULL ) {
        freeAndExpr( AndExpression->prevAndExpr );
    }

    free( AndExpression->prevAndExpr );
    AndExpression->prevAndExpr = NULL;

}