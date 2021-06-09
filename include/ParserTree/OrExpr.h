
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

    /**
     * \addtogroup OrExpression
     * @{
     */

    typedef struct OrExpr OrExpr;
    
    OrExpr* new_OrExpr( AndExpr* expr );
    OrExpr* append_ToOrExpr_AndExpr( OrExpr* expr, AndExpr* AndExpression );
    
    unsigned int getOrExpr_id( OrExpr* expr );

    void freeOrExpr( OrExpr* OrExpression );
    void printOrExpr( OrExpr* OrExpression );
    void build_Graphviz_OrExpr( OrExpr* OrExpression, FILE* fp );

    /** @} */

#endif
