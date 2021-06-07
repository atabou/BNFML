
/**
 * 
 * @file AndExpr.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the AndExpr struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "BNF.h"

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param symbol A pointer to a **Symbol** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* createAndExpr( Symbol* symbol ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = NULL;
    a->symbol = symbol;

    return a;

}

/**
 * @brief Constructor to append a new **Symbol** to an existing **AndExpr** object.
 * 
 * @param lst A pointer to an existing **AndExpr** object.
 * @param symbol A pointer to a **Symbol** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = lst;
    a->symbol = symbol;

    return a;

}

/**
 * @brief Destructor for an **AndExpr** object.
 * 
 * @param AndExpression A pointer to the **AndExpr** object you want to destruct.
 */
void freeAndExpr(AndExpr* AndExpression) {

    freeSymbol( AndExpression->symbol );
    free( AndExpression->symbol );
    AndExpression->symbol = NULL;

    if( AndExpression->prevAndExpr != NULL ) {
        freeAndExpr( AndExpression->prevAndExpr );
    }

    free( AndExpression->prevAndExpr );
    AndExpression->prevAndExpr = NULL;

}

/**
 * @brief Prints a string representation of an **AndExpr** object.
 * 
 * @param AndExpression A pointer to the **AndExpr** object you want to print.
 */
void printAndExpr( AndExpr* AndExpression ) {

    printSymbol(AndExpression->symbol);

    if( AndExpression->prevAndExpr != NULL ) {

        printf(" ");
        printAndExpr( AndExpression->prevAndExpr );

    }

}

/**
 * @brief Internal function to build a graphiz representation of the dependencies of an **AndExpr**. (Used by **buildAndExprNode**)
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param fp A valid file pointer.
 * @param id The id of the "top level" **AndExpr**. 
 */
void buildAndExprArrows( AndExpr* AndExpression, FILE* fp, unsigned int id ) {

    fprintf( fp, "%u -> %u;\n", id, AndExpression->symbol->id );
    buildSymbolNode( AndExpression->symbol, fp );

    if( AndExpression->prevAndExpr != NULL ) {
        buildAndExprArrows( AndExpression->prevAndExpr, fp, id );
    }

}

/**
 * @brief Builds a graphviz representation of an **AndExpr** object and prints it to a file.
 * 
 * @param AndExpression A pointer to an **AndExpression** object.
 * @param fp A valid file pointer.
 */
void buildAndExprNode( AndExpr* AndExpression, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", AndExpression->id, "AND" );
    buildAndExprArrows( AndExpression, fp, AndExpression->id );

}