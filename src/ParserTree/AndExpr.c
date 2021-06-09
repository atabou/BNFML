
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

#include "AndExpr.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include "Common.h"

/**
 * @enum SymbolType
 * @brief Enum to represent the types a symbol can be.
 * 
 */
enum SymbolType {

    TERMINAL_SYMBOL, /**< Enum value to reprsent a **Terminal** value. */
    NON_TERMINAL_SYMBOL /**< Enum value to represent a **NonTerminal** value. */

};

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
    s->term = nterm;

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

int getAndExpr_id( AndExpr* expr ) {
    return expr->id;
}

/**
 * @brief Destructor for an **AndExpr** object.
 * 
 * @param expr A pointer to the **AndExpr** object you want to destruct.
 */
void freeAndExpr(AndExpr* expr) {

    for( int i=0; i<expr->n; i++ ) {
        
        if( expr->branches[i]->type == TERMINAL_SYMBOL ) {

            freeTerminal( expr->branches[i]->term );
            

        } else if ( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            freeNonTerminal( expr->branches[i]->nterm );
            
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
            printTerminal(expr->branches[i]->term);
        } else if( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {
            printNonTerminal(expr->branches[i]->nterm);
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

            fprintf( fp, "%u -> %u [label=\"Terminal\"];\n", expr->id, getTerminal_id( expr->branches[i]->term ) );
            build_Graphviz_Terminal( expr->branches[i]->term, fp );

        } else if( expr->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", expr->id, getNonTerminal_id( expr->branches[i]->nterm ) );
            build_Graphviz_NonTerminal(expr->branches[i]->nterm, fp);

        }

    }

}