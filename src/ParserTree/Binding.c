/**
 * 
 * @file Binding.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the Binding struct related functions.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Binding.h"
#include "NonTerminal.h"
#include "OrExpr.h"
#include "Common.h"

/**
 * @struct **Binding**
 * @brief struct to define a parsed **Binding** value in BNFML
 * 
 */
struct Binding {

    unsigned int id; /**< Global ID of the object. see: idGenerator*/
    NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
    OrExpr* OrExpression; /**< A pointer to a **OrExpr** object.*/

}; 

/**
 * @brief Constructor to create an **Binding** object.
 * 
 * @param nterm A pointer to a **NonTerminal** object.
 * @param OrExpression A pointer to an **OrExpr** object.
 * @return Binding* Pointer to a newly created **Binding** object.
 */
Binding* new_Binding( NonTerminal* nterm, OrExpr* OrExpression ) {

    Binding* b = (Binding*) malloc(sizeof(Binding));

    b->id = ParserID_Generator++;
    b->nterm = nterm;
    b->OrExpression = OrExpression;

    return b; 

}

unsigned int getBinding_id( Binding* b ) {
    return b->id;
}

/**
 * @brief Destructor for a **Binding** object.
 * 
 * @param binding A pointer to the **Binding** object you want to destruct.
 */
void freeBinding(Binding* binding) {

    freeNonTerminal(binding->nterm);
    free( binding->nterm );
    binding->nterm = NULL;

    freeOrExpr( binding->OrExpression );
    free( binding->OrExpression );
    binding->OrExpression = NULL;

}

/**
 * @brief Prints a string representation of a **Binding** object.
 * 
 * @param b A pointer to the **Binding** object you want to print.
 */
void printBinding( Binding* b ) {

    printNonTerminal( b->nterm );
    printf( " ::= " );
    printOrExpr( b->OrExpression );

}

/**
 * @brief Builds a graphviz representation of a **Binding** object and prints it to a file.
 * 
 * @param b A pointer to an **Binding** object.
 * @param fp A valid file pointer.
 */
void build_Graphviz_Binding( Binding* b, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", b->id, "Binding" );

    fprintf( fp, "%u -> %u [label=\"Non-Terminal\"];\n", b->id, getNonTerminal_id( b->nterm ) );
    buildNonTerminalNode( b->nterm, fp );

    fprintf( fp, "%u -> %u [label=\"Or-Expression\"];\n", b->id, getOrExpr_id( b->OrExpression ) );
    buildOrExprNode( b->OrExpression, fp );

}