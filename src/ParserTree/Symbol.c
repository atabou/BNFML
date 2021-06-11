
#include <stdlib.h>

#include "ParserTree/Symbol.h"
#include "Common.h"

unsigned int symbolGetID( Symbol* this );
void symbolDestructor( Symbol* this );

Symbol* new_Symbol( ) {

    printf( "Creating new Symbol.\n" );

    Symbol* s = (Symbol*) malloc( sizeof(Symbol) );

    s->id = ParserID_Generator++;

    s->getID = symbolGetID;
    s->destruct = symbolDestructor;

    printf( "[SUCCESS] Finished creating Terminal symbol.\n" );

    return s;

}

unsigned int symbolGetID( Symbol* this ) {

    return this->id;

}

void symbolDestructor( Symbol* this ) {

    return ;

}