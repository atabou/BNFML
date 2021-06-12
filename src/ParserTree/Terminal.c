
/**
 * 
 * @file Terminal.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Implementation file for the struct **Terminal** and its related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/Terminal.h"
#include "ParserTree/Symbol.h"
#include "Common.h" 

char* terminalValueGet( Terminal* this );

unsigned int inheritedGetID( Terminal* this );

void terminalPrint( Terminal* this );
void dispatchPrint( Symbol* super );

void terminalBuildGraphviz( Terminal* this, FILE* fp );
void dispatchBuildGraphviz( Symbol* super, FILE* fp );

enum SymbolType dynamictype_Terminal_AND_Dispatch(  );

void terminalDestruct( Terminal* this );
void dispatchDestruct( Symbol* super );


Terminal* new_Terminal( char* value ) {

    printf( "Creating a Terminal expression.\n" );

    Terminal* term = (Terminal*) malloc(sizeof(Terminal));

    // Allocate memory, and assign a value to the private fields.
    term->super = *new_Symbol( );

    // Populate private variables
    term->value = value;

    // Class methods
    term->getValue = terminalValueGet;
    term->getID = inheritedGetID;

    // Implementation of abstract methods
    term->print = terminalPrint;
    term->build_Graphviz = terminalBuildGraphviz;
    term->destruct = terminalDestruct;
    term->getDynamicType = dynamictype_Terminal_AND_Dispatch;

    // Method dispatch
    term->super.print = dispatchPrint;
    term->super.build_Graphviz = dispatchBuildGraphviz;
    term->super.getDynamicType = dynamictype_Terminal_AND_Dispatch;


    printf( "[SUCCESS] Finished creating a Terminal expression.\n" );

    return term;

}

unsigned int inheritedGetID( Terminal* this ) {

    return this->super.getID( (Symbol*) this );

}

char* terminalValueGet( Terminal* this ) {

    return this->value;

}

void terminalDestruct( Terminal* this ) {
    
    printf( "Freeing Terminal with id: %d and value: %s\n", this->getID(this), this->getValue(this) );

    free( this->value );
    this->value = NULL;

    this->super.destruct( (Symbol*) this );

    // TODO super was created on the heap, verify how it should be dealt with. The following does not work.
    // free( &(this->super) );

    printf( "Freeing Terminal with id: %d and value: %s\n", this->getID(this), this->getValue(this) );

}

void terminalPrint( Terminal* this ) {

    printf( "'%s'", this->value );

}

void dispatchPrint( Symbol* super ) {

    Terminal* this = (Terminal*) super;
    this->print( this );

}

void terminalBuildGraphviz( Terminal* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID( this ), this->value );

}

void dispatchBuildGraphviz( Symbol* super, FILE* fp ) {

    Terminal* this = (Terminal*) super;
    this->build_Graphviz( this, fp );

}

enum SymbolType dynamictype_Terminal_AND_Dispatch(  ) {
    return TERMINAL_SYMBOL;
}