
%{

#include <stdio.h>
#include <string.h>

%}

%option noyywrap
%option yylineno

NonTerminal             <.+>
Terminal                '
OR                      [\n\t\r ]*\|[\n\t\r ]*

%%

{NonTerminal}           { return NON_TERMINAL_VAL; }
{Terminal}              { return TERMINAL_VAL; }
::=                     { return ASSIGN; }
{OR}                    { return PIPE; }
[\t ]+                  { return AND; }
[\r\n]                    /*Do nothing*/
.                       { printf("Error"); }

%%

char* iterateOverTerminal() {

    string s = "";

    char current = input();
    while( true ) {

        if( current == '\n' ) {
            
            log.Error("Missing quote: '");
            exit(-1);

        } else if ( current == '\'' ) {
        
            break;
        
        } else if (current == '\\') {

            char checkNext = input();

            if(checkNext == '\'') {
                s += checkNext;
            } else {
                s = s + current + checkNext;
            }


        } else {

            s += current;

        }

        current = input();

    }

    return s;

}