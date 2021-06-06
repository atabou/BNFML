
%{

#include <stdio.h>

#include "./include/BNF.h"

#define YYDEBUG 1

extern FILE *yyin;
FILE* outFile;

int yylex();
void yyerror(const char* s);

/* Extern Variables */
unsigned int idGenerator;

%}

%union {

    char*                       terminal_value;
    char*                       non_terminal_value;
    BindingList*                bindingList;
    Binding*                    binding;
    OrExpr*                     orExpr;
    AndExpr*                    andExpr;
    Symbol*                     symbol;
    NonTerminal*                nonTerm;
    Terminal*                   term;

}

/* Terminals */

%token  <terminal_value>        TERMINAL_VAL
%token  <non_terminal_value>    NON_TERMINAL_VAL
%token                          ASSIGN
%token                          PIPE
%token                          NL

/* Non-Terminals */

%type   <bindingList>           binding_list
%type   <binding>               binding
%type   <orExpr>                or_expression
%type   <andExpr>               and_expression
%type   <symbol>                symbol
%type   <nonTerm>               non_terminal
%type   <term>                  terminal


/* Start Symbol */

%start                          bnf


/* Precedence and Associativity */

%left                           NL
%left                           ASSIGN
%left                           PIPE

%%

bnf
    : binding_list                              { printBindingList($1); freeBindingList($1); free($1); }
    ;


binding_list
    : binding_list NL binding                   { $$ = appendBinding($1, $3); }
    | binding                                   { $$ = createBindingListFromBinding($1); }
    ;

binding
    : non_terminal ASSIGN or_expression         { $$ = createBinding( $1, $3 ); } 
    ;

or_expression
    : or_expression PIPE and_expression         { $$ = appendAndExpr( $1, $3 ); } 
    | and_expression                            { $$ = createOrExpr( $1 ); } 
    ;

and_expression
    : and_expression symbol                     { $$ = appendSymbol($1, $2); } 
    | symbol                                    { $$ = createAndExpr($1); } 
    ; 

symbol
    : non_terminal                              { $$ = createNonTerminalSymbol($1); } 
    | terminal                                  { $$ = createTerminalSymbol($1); } 
    ;

non_terminal
    : NON_TERMINAL_VAL                          { $$ = createNonTerminal($1); }
    ;

terminal
    : TERMINAL_VAL                              { $$ = createTerminal($1); }
    ;


%%

#include <stdlib.h>
int main(int argc, char **argv){

    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    // Initialise Global Variables;
    idGenerator = 0;

    if( argc < 2 ) {
        printf( "Please provide a file to process." );
        exit(-1); 
    }

    const char* inFileName = argv[1];
    yyin = fopen(inFileName, "r");
    
    do {
        yyparse();
    } while(!feof(yyin));
    
    fclose(yyin);

    return 0;

}

void yyerror(const char* s) {

    printf( "ID Generator: %d\n", idGenerator );
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);

}