/**
 * 
 * @file Binding.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the Binding struct related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/Binding.h"
#include "ParserTree/NonTerminal.h"
#include "ParserTree/OrExpr.h"
#include "Common.h"

unsigned int id_GetBinding( Binding* bind );
NonTerminal* nterm_GetBinding( Binding* bind );
OrExpr* or_GetBinding( Binding* bind );

void print_Binding( Binding* bind );
void toGraphviz_Binding( Binding* bind, FILE* fp );

void destruct_Binding( Binding* bind );

Binding* new_Binding( NonTerminal* nterm, OrExpr* OrExpression ) {

    Binding* b = (Binding*) malloc(sizeof(Binding));

    b->id = ParserID_Generator++;
    b->nterm = nterm;
    b->OrExpression = OrExpression;

    b->getID = id_GetBinding;
    b->getNonTerminal = nterm_GetBinding;
    b->getOrExpr = or_GetBinding;

    b->print = print_Binding;
    b->toGraphviz = toGraphviz_Binding;

    b->destruct = destruct_Binding;

    return b; 

}

unsigned int id_GetBinding( Binding* this ) {
    return this->id;
}

NonTerminal* nterm_GetBinding( Binding* this ) {
    return this->nterm;
}

OrExpr* or_GetBinding( Binding* this ) {
    return this->OrExpression;
}

void print_Binding( Binding* this ) {
    
    NonTerminal* nterm = this->getNonTerminal( this );
    nterm->print( nterm );

    printf( " ::= " );

    OrExpr* expr = this->getOrExpr( this );
    expr->print( expr );

}

void toGraphviz_Binding( Binding* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), "Binding" );

    NonTerminal* nterm = this->getNonTerminal( this );
    fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", this->getID(this), nterm->getID(nterm) );
    nterm->build_Graphviz( nterm, fp );

    OrExpr* expr = this->getOrExpr( this );
    fprintf( fp, "%u -> %u [label=\"Or-Expression\"];\n", this->getID(this), expr->getID( expr ) );
    expr->toGraphviz( expr, fp );

}

void destruct_Binding(Binding* this) {

    NonTerminal* nterm = this->getNonTerminal(this);
    nterm->destruct( nterm );
    free( nterm );

    this->nterm = NULL;

    OrExpr* expr = this->OrExpression;
    expr->destruct( expr );
    free( expr );

    this->OrExpression = NULL;

}