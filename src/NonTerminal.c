#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"

NonTerminal* createNonTerminal( char* Name ) {

    NonTerminal* nt = (NonTerminal*) malloc(sizeof(NonTerminal));

    nt->id = idGenerator++;
    nt->Name = Name;

    return nt;

}

void freeNonTerminal( NonTerminal* nterm ) {

    free(nterm->Name);
    nterm->Name = NULL;
    
}

void printNonTerminal( NonTerminal* nterm ) {

    printf( "%s", nterm->Name );

}

void buildNonTerminalNode( NonTerminal* nterm, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", nterm->id, nterm->Name );

}