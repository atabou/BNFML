#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct OrExpr {

    unsigned int id;
    OrExpr* prevOrExpr;
    AndExpr* AndExpression;

};

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