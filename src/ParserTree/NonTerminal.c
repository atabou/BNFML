/**
 * 
 * @file NonTerminal.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the NonTerminal struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/NonTerminal.h"
#include "ParserTree/Symbol.h"
#include "Common.h"

char* name_Get( NonTerminal* this );

unsigned int inherited_idGet( NonTerminal* this );

void print_NonTerminal( NonTerminal* this );
void print_Dispatch( Symbol* super );

void graphviz_NonTerminal( NonTerminal* this, FILE* fp );
void graphviz_Dispatch( Symbol* super, FILE* fp );

enum SymbolType dynamictype_NonTerminal_AND_Dispatch(  );

void destruct_NonTerminal( NonTerminal* this );
void destruct_Dispatch( Symbol* super );

NonTerminal* new_NonTerminal( char* name ) {

    printf( "Creating a Non-Terminal expression.\n" );

    NonTerminal* nterm = (NonTerminal*) malloc(sizeof(NonTerminal));

    nterm->super = *new_Symbol();

    nterm->name = name;

    // Class methods
    nterm->getName = name_Get;
    nterm->getID = inherited_idGet;

    // Implementation of abstract methods
    nterm->print = print_NonTerminal;
    nterm->build_Graphviz = graphviz_NonTerminal;
    nterm->getDynamicType = dynamictype_NonTerminal_AND_Dispatch;
    nterm->destruct = destruct_NonTerminal;

    // Method dispatch
    nterm->super.print = print_Dispatch;
    nterm->super.build_Graphviz = graphviz_Dispatch;
    nterm->super.getDynamicType = dynamictype_NonTerminal_AND_Dispatch;

    printf( "[SUCCESS] Finished creating a Non-Terminal expression.\n" );

    return nterm;

}


char* name_Get( NonTerminal* this ) {

    return this->name;

}

unsigned int inherited_idGet( NonTerminal* this ) {

    return this->super.getID( (Symbol*) this );

}

void print_NonTerminal( NonTerminal* this ) {

    printf( "%s", this->name );

}

void print_Dispatch( Symbol* super ) {

    NonTerminal* this = (NonTerminal*) super;
    this->print( this );

}

void graphviz_NonTerminal( NonTerminal* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), this->name );

}

void graphviz_Dispatch( Symbol* super, FILE* fp ) {

    NonTerminal* this = (NonTerminal*) super;
    this->build_Graphviz( this, fp );

}

enum SymbolType dynamictype_NonTerminal_AND_Dispatch( NonTerminal* nterm ) {

    return NON_TERMINAL_SYMBOL;

}

void destruct_NonTerminal( NonTerminal* this ) {

    printf( "Freeing Non-Terminal with id: %d and name: %s\n", this->getID(this), this->getName(this) );

    free(this->name);
    this->name = NULL;

    this->super.destruct( (Symbol*) this );


    // TODO super was created on the heap, verify how it should be dealt with. The following does not work.
    // free( &(this->super) );

    printf( "Freeing Binding with id: %d, and name: %s\n", this->getID(this), this->getName(this) );
}

void destruct_Dispatch( Symbol* super );