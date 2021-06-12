
%{

#include <stdio.h>

#include "Common.h"
#include "ParserTree.h"
#include "ExecutionGraph.h"

extern FILE *yyin;
FILE* outFile;

int yylex();
void yyerror(const char* s);


/* Function Declarations */
void doThis( BindingList* lst );

/* Extern Variables */
unsigned int ParserID_Generator;
unsigned int ExecutionID_Generator;
// unsigned int executionTreeIDGenerator;

%}

%union {

    char*                       terminal_value;
    char*                       non_terminal_value;
    BindingList*                bindingList;
    Binding*                    binding;
    OrExpr*                     orExpr;
    AndExpr*                    andExpr;
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
    : binding_list                              { doThis($1); }
    ;

binding_list
    : binding_list NL binding                   { $$ = append_ToBindingList_Binding($1, $3); }
    | binding                                   { $$ = new_BindingList( $1 ); }
    ;

binding
    : non_terminal ASSIGN or_expression         { $$ = new_Binding( $1, $3 ); }
    ;

or_expression
    : or_expression PIPE and_expression         { $$ = append_ToOrExpr_AndExpr( $1, $3 ); } 
    | and_expression                            { $$ = new_OrExpr( $1 ); } 
    ;

and_expression
    : and_expression non_terminal               { $1->append( $1, (Symbol*) $2 ); $$ = $1; }
    | and_expression terminal                   { $1->append( $1, (Symbol*) $2 ); $$ = $1; }
    | non_terminal                              { $$ = new_AndExpr( (Symbol*) $1); }
    | terminal                                  { $$ = new_AndExpr( (Symbol*) $1); }
    ; 

non_terminal
    : NON_TERMINAL_VAL                          { $$ = new_NonTerminal($1); }
    ;

terminal
    : TERMINAL_VAL                              { $$ = new_Terminal($1); }
    ;


%%

#include <stdlib.h>

void doThis( BindingList* lst ) {

    printBindingList( lst );

    FILE* fp = fopen( "log/ParseTree.dot", "w" );
    
    fprintf( fp, "digraph tree {\n" );
    build_Graphviz_BindingList( lst, fp );
    fprintf( fp, "}\n" );

    fclose(fp);

    ExecutionGraph* G = buildExecutionGraph( lst );

    freeBindingList( lst );
    free( lst );

    fp = fopen( "log/ExecutionGraph.dot", "w" );

    fprintf( fp, "digraph tree {\n" );
    buildGraphvizExecutionGraphRepresentation( G, fp );
    fprintf( fp, "}\n" );

    fclose(fp);

    freeExecutionGraph( G );
    free( G );

}

int main(int argc, char **argv){

    // Initialise Global Variables;
    ParserID_Generator = 0;
    ExecutionID_Generator = 0;

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

    printf( "ID Generator: %d\n", ParserID_Generator );
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);

}