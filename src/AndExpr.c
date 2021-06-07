
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
 * @param term A pointer to a **Terminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* createTerminalAndExpr( Terminal* term ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = NULL;
    a->type = TERM;
    a->term = term;

    return a;

}

/**
 * @brief Constructor to create an **AndExpr** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* createNonTerminalAndExpr( NonTerminal* nterm ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = NULL;
    a->type = NONTERM;
    a->nterm = nterm;

    return a;

}


/**
 * @brief Constructor to append a new **Terminal** to an existing **AndExpr** object.
 * 
 * @param lst A pointer to an existing **AndExpr** object.
 * @param term A pointer to a **Terminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* appendTerminal( AndExpr* lst, Terminal* term ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = lst;
    a->type = TERM;
    a->term = term;
    
    return a;

}

/**
 * @brief Constructor to append a new **NonTerminal** to an existing **AndExpr** object.
 * 
 * @param lst A pointer to an existing **AndExpr** object.
 * @param nterm A pointer to a **NonTerminal** object.
 * @return AndExpr* Pointer to a newly created **AndExpr** object.
 */
AndExpr* appendNonTerminal( AndExpr* lst, NonTerminal* nterm ) {

    AndExpr* a = (AndExpr*) malloc(sizeof(AndExpr));

    a->id = idGenerator++;
    a->prevAndExpr = lst;
    a->type = NONTERM;
    a->nterm = nterm;
    
    return a;

}

/**
 * @brief Destructor for an **AndExpr** object.
 * 
 * @param AndExpression A pointer to the **AndExpr** object you want to destruct.
 */
void freeAndExpr(AndExpr* AndExpression) {

    if( AndExpression->type == TERM ) {

        freeTerminal( AndExpression->term );
        free( AndExpression->term );
        AndExpression->term = NULL;

    } else {

        freeNonTerminal( AndExpression->nterm );
        free( AndExpression->nterm );
        AndExpression->nterm = NULL;

    }

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

    if( AndExpression->type == TERM ) {
        printTerminal(AndExpression->term);
    } else {
        printNonTerminal(AndExpression->nterm);
    }

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

    if( AndExpression->type == TERM ) {
        fprintf( fp, "%u -> %u [label=\"Terminal\"];\n", id, AndExpression->term->id );
        buildTerminalNode( AndExpression->term, fp );
    } else {
        fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", id, AndExpression->nterm->id );
        buildNonTerminalNode(AndExpression->nterm, fp);
    }

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