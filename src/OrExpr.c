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

#include "BNF.h"

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param AndExpression A pointer to a **AndExpr** object.
 * @return OrExpr* Pointer to a newly created **OrExpr** object.
 */
OrExpr* createOrExpr( AndExpr* AndExpression ) {

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    o->id = idGenerator++;
    o->prevOrExpr = NULL;
    o->AndExpression = AndExpression;

    return o;

}

/**
 * @brief Constructor to append a new **AndExpr** to an existing **OrExpr** object.
 * 
 * @param lst A pointer to an existing **OrExpr** object.
 * @param AndExpression A pointer to a **AndExpr** object.
 * @return OrExpr* Pointer to a newly created **OrExpression** object.
 */
OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression ) {

    OrExpr* o = (OrExpr*) malloc(sizeof(OrExpr));

    o->id = idGenerator++;
    o->prevOrExpr = lst;
    o->AndExpression = AndExpression;

    return o;

}

/**
 * @brief Destructor for an **OrExpr** object.
 * 
 * @param OrExpression A pointer to the **OrExpr** object you want to destruct.
 */
void freeOrExpr(OrExpr* OrExpression) {

    freeAndExpr( OrExpression->AndExpression );
    free( OrExpression->AndExpression );
    OrExpression->AndExpression = NULL;

    if( OrExpression->prevOrExpr != NULL ) {
        freeOrExpr(OrExpression->prevOrExpr);
    }

    free(OrExpression->prevOrExpr);
    OrExpression->prevOrExpr = NULL;

}

/**
 * @brief Prints a string representation of an **OrExpr** object.
 * 
 * @param OrExpression A pointer to the **OrExpr** object you want to print.
 */
void printOrExpr( OrExpr* OrExpression ) {

    printAndExpr( OrExpression->AndExpression );

    if( OrExpression->prevOrExpr != NULL ) {

        printf(" | ");
        printOrExpr(OrExpression->prevOrExpr);

    }

}

/**
 * @brief Internal function to build a graphiz representation of the dependencies of an **OrExpr**. (Used by **buildOrExprNode**)
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param fp A valid file pointer.
 * @param id The id of the "top level" **OrExpr**. 
 */
void buildOrExprArrows( OrExpr* OrExpression, FILE* fp, unsigned int id ) {

    fprintf( fp, "%u -> %u;\n", id, OrExpression->AndExpression->id );
    buildAndExprNode( OrExpression->AndExpression, fp );

    if( OrExpression->prevOrExpr != NULL ) {
        buildOrExprArrows( OrExpression->prevOrExpr, fp, id );
    }

}


/**
 * @brief Builds a graphviz representation of an **OrExpr** object and prints it to a file.
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param fp A valid file pointer.
 */
void buildOrExprNode( OrExpr* OrExpression, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", OrExpression->id, "OR" );
    buildOrExprArrows( OrExpression, fp, OrExpression->id );

}