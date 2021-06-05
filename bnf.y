
%{

#include <stdio.h>

#include "./include/BNF.h"

extern FILE *yyin;
FILE* outFile;

int yylex();
void yyerror(const char* s);

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
%token                          AND
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
%left                           AND                       

%%

bnf
    : binding_list
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
    : and_expression AND symbol                 { $$ = appendSymbol($1, $3); }
    | symbol                                    { $$ = createAndExpr($1); }
    ; 

symbol
    : non_terminal                              { $$ = createNonTerminalSymbol($1); }
    | terminal                                  { $$ = createTerminalSymbol($1); }
    ;

non_terminal
    : TERMINAL_VAL                              { $$ = createNonTerminal($1); }
    ;

terminal
    : NON_TERMINAL_VAL                          { $$ = createTerminal($1); }
    ;


%%

#include <stdlib.h>
int main(int argc, char **argv){
    idGenerator = 0;
    // const char* inFileName = (argc > 1)?argv[1]:"test.sml";
    // const char* outFileName = (argc > 2)?argv[2]:"test.dot";
    // yyin = fopen(inFileName, "r");
    // outFile = fopen(outFileName, "w");
    // fprintf(outFile, "digraph tree {\n");
    // do {
    //     yyparse();
    // } while(!feof(yyin));
    // fprintf(outFile, "}\n");
    // fclose(yyin);
    // fclose(outFile);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}