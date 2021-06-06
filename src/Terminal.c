
#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"

Terminal* createTerminal( char* Regex ) {

    Terminal* t = (Terminal*) malloc(sizeof(Terminal));

    t->id = idGenerator++;
    t->regex = Regex;

    return t;

}

void freeTerminal( Terminal* term ) {

    free( term->regex );
    term->regex = NULL;

}

void printTerminal( Terminal* term ) {

    printf( "'%s'", term->regex );

}

void buildTerminalNode( Terminal* term, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", term->id, term->regex );

}