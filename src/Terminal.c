#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct Terminal {

    unsigned int id;
    char* regex;

};

Terminal* createTerminal( char* Regex ) {

    Terminal* t = (Terminal*) malloc(sizeof(Terminal));

    t->id = idGenerator++;
    t->regex = Regex;

    return t;

}