

#include "../../include/ParserTree/Symbol.h"
#include "../../include/ParserTree/Terminal.h"
#include "../../include/Common.h"

#include <string.h>
#include <stdio.h>

unsigned int ParserID_Generator;

int IntEquals( char* name, int x, int y ) {

    if ( x == y ) {

        printf( "\t[PASS] %s\n", name );
        return 1;

    } else {

        printf( "\t[FAIL] %s\n", name );
        return 0;

    }

}

int StringEquals( char* name, char* x, char* y ) {

    if ( strcmp( x, y ) == 0 ) {

        printf( "\t[PASS] %s\n", name );
        return 1;

    } else {

        printf( "\t[FAIL] %s\n", name );
        return 0;

    }

}

void RunSuite( char* SuiteName ) {

    printf( "\nTestSuite: %s\n\n", SuiteName );

    Terminal* term = new_Terminal( "Hello" );
    Symbol* sym = (Symbol*) term;
    Terminal* recast = (Terminal*) sym;

    int success = 1;

    success *= IntEquals( "GetID of Terminal: ", term->getID( term ), 0 );
    success *= StringEquals( "GetValue of Terminal", term->getValue( term ), "Hello" );
    success *= IntEquals( "GetID of Symbol", sym->getID( sym ), 0 );
    success *= StringEquals( "GetValue of re-casted Terminal", recast->getValue( recast ), "Hello" );

    if( success ) {
        printf( "\n[SUCCESS]: All tests passed.\n" );
    } else {
        printf( "[FAIL] Test Suite: %s, failed.\n", SuiteName );
    }
}

int main( ) {

    ParserID_Generator = 0;
    
    RunSuite("First Test");

    return 0;

}