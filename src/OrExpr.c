#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"


OrExpr* createOrExpr( AndExpr* AndExpression ) {

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    o->id = idGenerator++;
    o->prevOrExpr = NULL;
    o->AndExpression = AndExpression;

    return o;

}

OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression ) {

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    o->id = idGenerator++;
    o->prevOrExpr = lst;
    o->AndExpression = AndExpression;

    return o;

}

void freeOrExpr(OrExpr* OrExpression) {

    freeAndExpr( OrExpression->AndExpression );
    free( OrExpression->AndExpression );
    OrExpression->AndExpression = NULL;

    if( OrExpression->prevOrExpr != NULL ) {
        freeOrExpr(OrExpression->prevOrExpr);
    }

    free(OrExpression->prevOrExpr);
    OrExpression->prevOrExpr = NULL;

}

void printOrExpr( OrExpr* OrExpression ) {

    printAndExpr( OrExpression->AndExpression );

    if( OrExpression->prevOrExpr != NULL ) {

        printf(" | ");
        printOrExpr(OrExpression->prevOrExpr);

    }

}