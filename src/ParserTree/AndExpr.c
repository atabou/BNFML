
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

void freeAndExpr( AndExpr* expr );
void printAndExpr( AndExpr* this );
void build_Graphviz_AndExpr( AndExpr* this, FILE* fp );


unsigned int getAndExpr_id( AndExpr* this );
Symbol** getAndExpr_Branches( AndExpr* this );
int getAndExpr_length( AndExpr* this );


/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* new_AndExpr_Terminal( Terminal* term ) {

    printf( "Creating AND expression using a Terminal.\n" );

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = ParserID_Generator++;

    a->branches = (Symbol**) malloc( sizeof( Symbol* ) );
    a->n = 1;

    Symbol* s = new_Symbol_Terminal( term );
    a->branches[0] = s;

    // Getters
    a->getID = getAndExpr_id;
    a->getBranches = getAndExpr_Branches;
    a->length = getAndExpr_length;

    a->print = printAndExpr;
    a->toGraphviz = build_Graphviz_AndExpr;
    a->destruct = freeAndExpr;
    
    printf( "[SUCCESS] Finished creating AND expression using a Terminal.\n" );

    return a;

}

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* new_AndExpr_NonTerminal( NonTerminal* nterm ) {

    printf( "Creating AND expression using a Non-Terminal.\n" );

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = ParserID_Generator++;

    a->branches = (Symbol**) malloc( sizeof( Symbol* ) );
    a->n = 1;

    Symbol* s = new_Symbol_NonTerminal( nterm );
    a->branches[0] = s;

    // Getters
    a->getID = getAndExpr_id;
    a->getBranches = getAndExpr_Branches;
    a->length = getAndExpr_length;

    a->print = printAndExpr;
    a->toGraphviz = build_Graphviz_AndExpr;
    a->destruct = freeAndExpr;

    printf( "[SUCCESS] Finished creating AND expression using a Non-Terminal.\n" );

    return a;

}


/**
 * @brief Constructor to append a new **Terminal** to an existing **AndExpr** object.
 * 
 * @param expr A pointer to an existing **AndExpr** object.
 * @param term A pointer to a **Terminal** object.
 */
AndExpr* append_ToAndExpr_Terminal( AndExpr* expr, Terminal* term ) {

    Symbol* s = new_Symbol_Terminal( term );

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

    Symbol* s = new_Symbol_NonTerminal( nterm );

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

unsigned int getAndExpr_id( AndExpr* this ) {
    return this->id;
}

Symbol** getAndExpr_Branches( AndExpr* this ) {
    return this->branches;
}

int getAndExpr_length( AndExpr* expr ) {
    return expr->n;
}

/**
 * @brief Destructor for an **AndExpr** object.
 * 
 * @param expr A pointer to the **AndExpr** object you want to destruct.
 */
void freeAndExpr(AndExpr* this) {

    for( int i=0; i<this->n; i++ ) {
        
        if( this->branches[i]->getType( this->branches[i] ) == TERMINAL_SYMBOL ) {

            this->branches[i]->getTerminal( this->branches[i] )->fn->destruct( this->branches[i]->getTerminal( this->branches[i] ) );

        } else if ( this->branches[i]->type == NON_TERMINAL_SYMBOL ) {

            this->branches[i]->getNonTerminal( this->branches[i] )->fn->destruct( this->branches[i]->getNonTerminal( this->branches[i] ) );
            
        }

        free( this->branches[i] );
        this->branches[i] = NULL;

    }

    free( this->branches );
    this->branches = NULL;
    this->n = 0;

}

/**
 * @brief Prints a string representation of an **AndExpr** object.
 * 
 * @param expr A pointer to the **AndExpr** object you want to print.
 */
void printAndExpr( AndExpr* this ) {

    for( int i=0; i<this->n; i++ ) {

        if( this->branches[i]->getType( this->branches[i] ) == TERMINAL_SYMBOL ) {

            this->branches[i]->getTerminal( this->branches[i] )->fn->print( this->branches[i]->getTerminal( this->branches[i] ) );
            
        } else if( this->branches[i]->getType( this->branches[i] ) == NON_TERMINAL_SYMBOL ) {

            this->branches[i]->getNonTerminal( this->branches[i] )->fn->print( this->branches[i]->getNonTerminal( this->branches[i] ) );

        }

        if( i < this->n - 1 ) {
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
void build_Graphviz_AndExpr( AndExpr* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this ->id, "AND" );

    for( int i=0; i < this->n; i++ ) {

        enum SymbolType type = this->branches[i]->getType( this->branches[i] );

        if( type == TERMINAL_SYMBOL ) {

            Terminal* term = this->branches[i]->getTerminal( this->branches[i] );

            fprintf( fp, "%u -> %u [label=\"Terminal\"];\n", this->id, term->fn->getID( term ));
            term->fn->build_Graphviz( term, fp );

        } else if( type == NON_TERMINAL_SYMBOL ) {

            NonTerminal* nterm = this->branches[i]->getNonTerminal( this->branches[i] );

            fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", this->id, nterm->fn->getID( nterm ) );
            nterm->fn->build_Graphviz(nterm, fp);

        }

    }

}