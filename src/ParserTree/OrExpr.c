/**
 * 
 * @file OrExpr.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the OrExpr struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/OrExpr.h"
#include "ParserTree/AndExpr.h"
#include "Common.h" 

// Getters
unsigned int id_Get(OrExpr* this);
AndExpr** branches_Get( OrExpr* this );
int length_Get( OrExpr* this );

//Methods
void print_OrExpr(OrExpr* this);
void graphviz_OrExpr(OrExpr* this, FILE* fp);
void append_OrExpr( OrExpr* this, AndExpr* AndExpression );

// Destructor
void destruct_OrExpr(OrExpr* this);

OrExpr* new_OrExpr( AndExpr* expr ) {

    printf( "Creating OR expression.\n" );

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    // Initialising Class Variables
    o->id = ParserID_Generator++;

    o->branches = (AndExpr**) malloc( sizeof( AndExpr* ) );
    o->branches[0] = expr;
    o->n = 1;

    // Getters
    o->getID = id_Get;
    o->getBranches = branches_Get;
    o->length = length_Get;

    o->append = append_OrExpr;

    o->print = print_OrExpr;
    o->toGraphviz = graphviz_OrExpr;
    o->destruct = destruct_OrExpr;

    printf( "[SUCCESS] Finished creating OR expression.\n" );

    return o;

}

// Getters
unsigned int id_Get(OrExpr* this) {
    return this->id;
}

AndExpr** branches_Get( OrExpr* this ) {
    return this->branches;
}

int length_Get( OrExpr* this ) {
    return this->n;
}

//Methods
void print_OrExpr(OrExpr* this) {

    for( int i = 0; i < this->length(this); i++ ) {

        this->getBranches(this)[i]->print( this->getBranches(this)[i] );
        
        if( i < this->length(this) - 1 ) {
            printf( " | " );
        }

    }

}

void graphviz_OrExpr(OrExpr* this, FILE* fp) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), "OR" );
    
    for( int i=0; i < this->length(this); i++ ) {

        AndExpr* expr = this->getBranches(this)[i];

        fprintf( fp, "%u -> %u;\n", this->getID(this), expr->getID( expr ) );
        expr->toGraphviz( expr, fp );

    }


}

void append_OrExpr( OrExpr* this, AndExpr* AndExpression ) {

    AndExpr** and_array = (AndExpr**) malloc( sizeof(AndExpr*) * (this->length(this) + 1) );

    for( int i=1; i<=this->length(this); i++ ) {
        and_array[i] = this->getBranches(this)[i-1];
    }

    and_array[0] = AndExpression;

    free( this->getBranches(this) );
    
    this->branches = and_array;
    this->n = this->length(this) + 1;

}

// Destructor
void destruct_OrExpr(OrExpr* this) {

    printf( "Freeing OR with id: %d\n", this->getID(this) );

    for( int i=0; i<this->length(this); i++ ) {

        this->getBranches(this)[i]->destruct( this->getBranches(this)[i] );
        free( this->getBranches(this)[i] );
        this->getBranches(this)[i] = NULL;

    }

    free( this->getBranches(this) );
    this->branches = NULL;
    this->n = 0;

    printf( "[SUCCESS] Freeing OR with id: %d\n", this->getID(this) );

}