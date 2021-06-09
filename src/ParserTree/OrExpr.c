/**
 * 
 * @file OrExpr.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the OrExpr struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ParserTree/OrExpr.h"
#include "ParserTree/AndExpr.h"
#include "Common.h"

/**
 * @struct **OrExpr**
 * @brief struct to define a parsed **OrExpr** value in BNFML
 * 
 */
struct OrExpr { // TODO OrExpression does not need to be a linked list

    unsigned int id; /**< Global ID of the object. see: idGenerator*/
    AndExpr** branches; /**< An array of pointers to **AndExpr** objects.*/
    int n; /** An integer representing the number of elements in AndExpression. */

}; 

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param expr A pointer to a **AndExpr** object.
 * @return OrExpr* Pointer to a newly created **OrExpr** object.
 */
OrExpr* new_OrExpr( AndExpr* expr ) {

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    o->id = ParserID_Generator++;

    o->branches = ( AndExpr** ) malloc( sizeof( AndExpr* ) );
    o->branches[0] = expr;
    o->n = 1;

    return o;

}

/**
 * @brief Constructor to append a new **AndExpr** to an existing **OrExpr** object.
 * 
 * @param expr A pointer to an existing **OrExpr** object.
 * @param AndExpression A pointer to a **AndExpr** object.
 * @return OrExpr* Pointer to a newly created **OrExpression** object.
 */
OrExpr* append_ToOrExpr_AndExpr( OrExpr* expr, AndExpr* AndExpression ) {

    AndExpr** and_array = (AndExpr**) malloc( sizeof(AndExpr*) * (expr->n + 1) );

    for( int i=0; i<expr->n; i++ ) {
        and_array[i] = expr->branches[i];
    }

    and_array[expr->n] = AndExpression;

    free( expr->branches );
    
    expr->branches = and_array;
    expr->n = expr->n + 1;

    return expr;

}


unsigned int getOrExpr_id( OrExpr* expr ) {
    return expr->id;
}


/**
 * @brief Destructor for an **OrExpr** object.
 * 
 * @param expr A pointer to the **OrExpr** object you want to destruct.
 */
void freeOrExpr(OrExpr* expr) {

    for( int i=0; i<expr->n; i++ ) {

        freeAndExpr( expr->branches[i] );
        free( expr->branches[i] );
        expr->branches[i] = NULL;

    }

    free( expr->branches );
    expr->branches = NULL;
    expr->n = 0;

}

/**
 * @brief Prints a string representation of an **OrExpr** object.
 * 
 * @param expr A pointer to the **OrExpr** object you want to print.
 */
void printOrExpr( OrExpr* expr ) {

    for( int i = 0; i < expr->n; i++ ) {

        printAndExpr( expr->branches[i] );
        
        if( i < expr->n - 1 ) {
            printf( " | " );
        }

    }

}

/**
 * @brief Builds a graphviz representation of an **OrExpr** object and prints it to a file.
 * 
 * @param expr A pointer to an **OrExpr** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_OrExpr( OrExpr* expr, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", expr->id, "OR" );
    
    for( int i=0; i < expr->n; i++ ) {

        fprintf( fp, "%u -> %u;\n", expr->id, getAndExpr_id( expr->branches[i] ) );
        build_Graphviz_AndExpr( expr->branches[i], fp );

    }

}