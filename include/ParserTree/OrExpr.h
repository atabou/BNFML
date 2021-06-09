
/**
 * 
 * @file OrExpr.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef OR_EXPR_H
    
    #define OR_EXPR_H

    #include <stdio.h>
    #include "AndExpr.h"

    typedef struct OrExpr OrExpr;

    /**
     * \addtogroup OrExpression
     * @{
     */

    /**
     * @struct **OrExpr**
     * @brief struct to define a parsed **OrExpr** value in BNFML
     * 
     */
    struct OrExpr { // TODO OrExpression does not need to be a linked list

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        AndExpr* AndExpression; /**< A pointer to a **AndExpr** object.*/

    }; 
    
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );
    
    void freeOrExpr( OrExpr* OrExpression );
    void printOrExpr( OrExpr* OrExpression );
    void buildOrExprNode( OrExpr* OrExpression, FILE* fp );

    /** @} */

#endif
