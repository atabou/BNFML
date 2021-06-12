
/**
 * 
 * @file AndExpr.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the **AndExpr** struct and its related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ParserTree/AndExpr.h"
#include "ParserTree/Symbol.h"
#include "ParserTree/Terminal.h"
#include "ParserTree/NonTerminal.h"
#include "Common.h"

// Getters
unsigned int id_Get(AndExpr* this);
Symbol** branches_Get( AndExpr* this );
int length_Get( AndExpr* this );

//Methods
void print_AndExpr(AndExpr* this);
void graphviz_AndExpr(AndExpr* this, FILE* fp);
void append_AndExpr( AndExpr* this, Symbol* sym );

// Destructor
void destruct_AndExpr(AndExpr* this);


/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* new_AndExpr ( Symbol* sym ) {

    printf( "Creating AND expression using a Non-Terminal.\n" );

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    // Initialising Class Variables
    a->id = ParserID_Generator++;

    a->branches = (Symbol**) malloc( sizeof( Symbol* ) );
    a->branches[0] = sym;
    a->n = 1;

    // Getters
    a->getID = id_Get;
    a->getBranches = branches_Get;
    a->length = length_Get;

    a->append = append_AndExpr;

    a->print = print_AndExpr;
    a->toGraphviz = graphviz_AndExpr;
    a->destruct = destruct_AndExpr;

    printf( "[SUCCESS] Finished creating AND expression using a Non-Terminal.\n" );

    return a;

}


// Getters
unsigned int id_Get(AndExpr* this) {
    return this->id;
}

Symbol** branches_Get( AndExpr* this ) {
    return this->branches;
}

int length_Get( AndExpr* this ) {
    return this->n;
}

//Methods
void print_AndExpr(AndExpr* this) {

    for( int i=0; i < this->n; i++ ) {

        this->branches[i]->print( this->branches[i] );
        if( i < this->n - 1 ) {
            printf(" ");
        }
        

    }

}

void graphviz_AndExpr(AndExpr* this, FILE* fp) {

    fprintf( fp, "%u [label=\"%s\"];\n", this ->id, "AND" );

    for( int i=0; i < this->n; i++ ) {

        Symbol* sym = this->branches[i];

        char* label;

        if( sym->getDynamicType() == TERMINAL_SYMBOL ) {

            label = strdup( "Terminal" );
        
        } else if ( sym->getDynamicType() == NON_TERMINAL_SYMBOL ) {
        
            label = strdup( "NonTerminal" );
        
        }

        fprintf( fp, "%u -> %u [label=\"%s\"];\n", this->id, sym->getID(sym), label);
        sym->build_Graphviz( sym, fp );

        free( label );

    }

}


void append_AndExpr( AndExpr* this, Symbol* sym ) {

    Symbol** sym_array = (Symbol**) malloc( sizeof(Symbol*) * (this->n + 1) );

    for( int i=1; i<=this->n; i++ ) {
        sym_array[i] = this->branches[i-1];
    }

    sym_array[0] = sym;

    free( this->branches );
    
    this->branches = sym_array;
    this->n = this->n + 1;

}


// TODO Get rid of the if statements and castings by doing a dispatch on the destructor of Terminal and NonTerminal.
void destruct_AndExpr(AndExpr* this) {

    for( int i=0; i<this->n; i++ ) {
        
        Symbol* sym = this->branches[i];

        if( sym->getDynamicType() == TERMINAL_SYMBOL ) {

           ( (Terminal*) sym )->destruct( (Terminal*) sym );


        } else if ( sym->getDynamicType() == NON_TERMINAL_SYMBOL ) {

            ( (NonTerminal*) sym )->destruct( (NonTerminal*) sym );
            
        }

        free( this->branches[i] );
        this->branches[i] = NULL;

    }

    free( this->branches );
    this->branches = NULL;
    this->n = 0;

}
