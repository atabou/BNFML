#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct NonTerminal {

    unsigned int id;
    char* Name;

};

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