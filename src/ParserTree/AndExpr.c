
/**
 * 
 * @file AndExpr.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the **AndExpr** struct and its related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/AndExpr.h"
#include "ParserTree/Terminal.h"
#include "ParserTree/NonTerminal.h"
#include "Common.h"

typedef struct Symbol {

    enum SymbolType type; /**< Enum **SymbolType** used to determine the type of symbol this object contains */
    union {
        NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
        Terminal* term; /**< A pointer to a **Terminal** object.*/
    };

} Symbol;

/**
 * @struct **AndExpr**
 * @brief struct to define a parsed **AndExpr** value in BNFML
 * 
 */
struct AndExpr { // TODO AndExpression does not need to be a linked list.

    unsigned int id; /**< Global ID of the object. see: idGenerator*/
    Symbol** branches; /**< Array of pointers to **Symbol** objects. */
    int n; /**< Integer representing the number of elements in the array */

};

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* new_AndExpr_Terminal( Terminal* term ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = ParserID_Generator++;

    a->branches = (Symbol**) malloc( sizeof( Symbol* ) );
    a->n = 1;

    Symbol* s = (Symbol*) malloc( sizeof(Symbol) );
    s->type = TERMINAL_SYMBOL;
    s->term = term;

    a->branches[0] = s;

    return a;

}

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* new_AndExpr_NonTerminal( NonTerminal* nterm ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = ParserID_Generator++;

    a->branches = (Symbol**) malloc( sizeof( Symbol* ) );
    a->n = 1;

    Symbol* s = (Symbol*) malloc( sizeof(Symbol) );
    s->type = NON_TERMINAL_SYMBOL;
    s->nterm = nterm;

    a->branches[0] = s;

    return a;

}


/**
 * @brief Constructor to append a new **Terminal** to an existing **AndExpr** object.
 * 
 * @param expr A pointer to an existing **AndExpr** object.
 * @param term A pointer to a **Terminal** object.
 */
AndExpr* append_ToAndExpr_Terminal( AndExpr* expr, Terminal* term ) {

    Symbol* s = (Symbol*) malloc( sizeof(Symbol) );
    s->type = TERMINAL_SYMBOL;
    s->term = term;

    Symbol** sym_array = (Symbol**) malloc( sizeof(Symbol*) * (expr->n + 1) );

    for( int i=0; i<expr->n; i++ ) {
        sym_array[i] = expr->branches[i];
    }

    sym_array[expr->n] = s;

    free( expr->branches );
    
    expr->branches = sym_array;
    expr->n = expr->n + 1;

    return expr;

}

/**
 * @brief Constructor to append a new **NonTerminal** to an existing **AndExpr** object.
 * 
 * @param expr A pointer to an existing **AndExpr** object.
 * @param nterm A pointer to a **NonTerminal** object.
 */
AndExpr* append_ToAndExpr_NonTerminal( AndExpr* expr, NonTerminal* nterm ) {

    Symbol* s = (Symbol*) malloc( sizeof(Symbol) );
    s->type = NON_TERMINAL_SYMBOL;
    s->nterm = nterm;

    Symbol** sym_array = (Symbol**) malloc( sizeof(Symbol*) * (expr->n + 1) );

    for( int i=0; i<expr->n; i++ ) {
        sym_array[i] = expr->branches[i];
    }

    sym_array[expr->n] = s;

    free( expr->branches );
    
    expr->branches = sym_array;
    expr->n = expr->n + 1;

    return expr;

}

unsigned int getAndExpr_id( AndExpr* expr ) {
    return expr->id;
}

enum SymbolType getAndExpr_type( AndExpr* expr, int i ) {

    if( i < 0 || i >= expr->n ) {

        printf( "Invalid integer argument: %d. Must be between 0 and %d. (getAndExpr_id)\n", i, expr->n );
        exit(-1);

    }

    return expr->branches[i]->type;

}

Terminal* getAndExpr_term( AndExpr* expr, int i ) {

    if( i < 0 || i >= expr->n ) {

        printf( "[ERROR] Invalid integer argument: %d. Must be between 0 and %d. (getAndExpr_term)\n", i, expr->n );
        exit(-1);

    }

    if( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

        printf( "[ERROR] The Symbol at %d is not a Terminal. (getAndExpr_term)\n", i );
        exit(-1);

    }

    return expr->branches[i]->term;

}

NonTerminal* getAndExpr_nterm( AndExpr* expr, int i ) {

    if( i < 0 || i >= expr->n ) {

        printf( "[ERROR] Invalid integer argument: %d. Must be between 0 and %d. (getAndExpr_nterm)\n", i, expr->n );
        exit(-1);

    }

    if( expr->branches[i]->type == TERMINAL_SYMBOL ) {

        printf( "[ERROR] The Symbol at %d is not a NonTerminal. (getAndExpr_nterm)\n", i );
        exit(-1);

    }

    return expr->branches[i]->nterm;

}

int getAndExpr_length( AndExpr* expr ) {
    return expr->n;
}


/**
 * @brief Destructor for an **AndExpr** object.
 * 
 * @param expr A pointer to the **AndExpr** object you want to destruct.
 */
void freeAndExpr(AndExpr* expr) {

    for( int i=0; i<expr->n; i++ ) {
        
        if( expr->branches[i]->type == TERMINAL_SYMBOL ) {

            expr->branches[i]->term->fn->destruct( expr->branches[i]->term );

        } else if ( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            expr->branches[i]->nterm->fn->destruct( expr->branches[i]->nterm );
            
        }

        free( expr->branches[i] );
        expr->branches[i] = NULL;

    }

    free( expr->branches );
    expr->branches = NULL;
    expr->n = 0;

}

/**
 * @brief Prints a string representation of an **AndExpr** object.
 * 
 * @param expr A pointer to the **AndExpr** object you want to print.
 */
void printAndExpr( AndExpr* expr ) {

    for( int i=0; i<expr->n; i++ ) {

        if( expr->branches[i]->type == TERMINAL_SYMBOL ) {

            expr->branches[i]->term->fn->print( expr->branches[i]->term );

        } else if( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            expr->branches[i]->nterm->fn->print( expr->branches[i]->nterm );

        }

        if( i < expr->n - 1 ) {
            printf(" ");
        }
        

    }

}

/**
 * @brief Builds a graphviz representation of an **AndExpr** object and prints it to a file.
 * 
 * @param expr A pointer to an **AndExpression** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_AndExpr( AndExpr* expr, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", expr->id, "AND" );

    for( int i=0; i < expr->n; i++ ) {

        if( expr->branches[i]->type == TERMINAL_SYMBOL ) {

            fprintf( fp, "%u -> %u [label=\"Terminal\"];\n", expr->id, expr->branches[i]->term->fn->getID( expr->branches[i]->term ) );
            expr->branches[i]->term->fn->build_Graphviz( expr->branches[i]->term, fp );

        } else if( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", expr->id, expr->branches[i]->nterm->fn->getID( expr->branches[i]->nterm ) );
            expr->branches[i]->nterm->fn->build_Graphviz(expr->branches[i]->nterm, fp);

        }

    }

}