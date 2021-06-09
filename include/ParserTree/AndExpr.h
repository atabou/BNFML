
/**
 * 
 * @file AndExpr.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef AND_EXPR_H
    
    #define AND_EXPR_H

    #include <stdio.h>

    #include "Terminal.h"
    #include "NonTerminal.h"

    

    /**
     * \addtogroup AndExpression
     * @{
     */


    typedef struct AndExpr AndExpr; 
    
    AndExpr* new_AndExpr_Terminal( Terminal* term );
    AndExpr* new_AndExpr_NonTerminal( NonTerminal* nterm );

    AndExpr* append_ToAndExpr_Terminal( AndExpr* expr, Terminal* term );
    AndExpr* append_ToAndExpr_NonTerminal( AndExpr* expr, NonTerminal* nterm );
    
    int getAndExpr_id( AndExpr* expr );
    void printAndExpr( AndExpr* AndExpression );
    void build_Graphviz_AndExpr( AndExpr* expr, FILE* fp );

    void freeAndExpr(AndExpr* AndExpression);

    /** @} */

#endif
