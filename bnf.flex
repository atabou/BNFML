
%{

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./include/BNF.h"
#include "bnf.tab.h"

char* iterateOverTerminal();
char* iterateOverNonTerminal();
char* concatenateStrings( char* s, char* cat );

%}

%option noyywrap
%option yylineno

NonTerminal             \<
Terminal                '
OR                      [\n\t\r ]*\|[\n\t\r ]*

%%

{NonTerminal}           { yylval.non_terminal_value = iterateOverNonTerminal(); return NON_TERMINAL_VAL; }
{Terminal}              { yylval.terminal_value = iterateOverTerminal(); return TERMINAL_VAL; }
::=                     { return ASSIGN; }
{OR}                    { return PIPE; }
[\n]+                   { return NL; }
[\r\t ]+                /*Do nothing*/
.                       { printf( "Error: %s\n", yytext ); exit(-1); }

%%

char* concatenateStrings( char* s, char* cat ) {

    if( s == NULL ) {
    
        s = (char*) malloc( sizeof(char)* (strlen(cat) + 1) );
        
        if( s == NULL ) {
            printf("Ran out of heap space");
            exit(-1);
        }
        
        s = strcpy( s, cat );

    } else {

        char cpy[ strlen(s) + 1 ];
        strcpy( cpy, s );

        free(s);

        s = (char*) malloc( sizeof( char ) * (strlen(cpy) + strlen(cat) + 1) );
        
        if( s == NULL ) {
            printf("Ran out of heap space");
            exit(-1);
        }

        strcpy(s, cpy);
        strcat(s, cat);

    }

    return s;

}

char* iterateOverNonTerminal() {

    char* s = concatenateStrings( NULL, "<" );
    char current = input();

    while( true ) {

        if( current == '\n' ) {
            
            printf("Missing closing bracket: >");
            exit(-1);

        } else if ( current == '>' ) {
        
            s = concatenateStrings( s, ">" );
            break;
        
        } else if (current == '\\') {

            char checkNext = input();

            if(checkNext == '>' || checkNext == '<') {

                char cat[2];

                cat[0] = checkNext;
                cat[1] = '\0';

                s = concatenateStrings( s, cat );

            } else {

                char cat[3];

                cat[0] = current;
                cat[1] = checkNext;
                cat[2] = '\0';

                s = concatenateStrings( s, cat );

            }


        } else {

            char cat[2];

            cat[0] = current;
            cat[1] = '\0';

            s = concatenateStrings( s, cat );

        }

        current = input();

    }

    return s;

}

char* iterateOverTerminal() {

    char* s = NULL;
    char current = input();

    while( true ) {

        if( current == '\n' ) {
            
            printf("Missing quote: '");
            exit(-1);

        } else if ( current == '\'' ) {
        
            break;
        
        } else if (current == '\\') {

            char checkNext = input();

            if(checkNext == '\'') {

                char* cat = "'";
                s = concatenateStrings( s, cat );

            } else {

                char cat[3];

                cat[0] = current;
                cat[1] = checkNext;
                cat[2] = '\0';

                s = concatenateStrings( s, cat );

            }


        } else {

            char cat[2];

            cat[0] = current;
            cat[1] = '\0';

            s = concatenateStrings( s, cat );

        }

        current = input();

    }

    return s;

}
