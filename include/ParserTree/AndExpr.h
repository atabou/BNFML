
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

    /**
     * @enum SymbolType
     * @brief Enum to represent the types a symbol can be.
     * 
     */
    enum SymbolType {

        TERMINAL_SYMBOL, /**< Enum value to reprsent a **Terminal** value. */
        NON_TERMINAL_SYMBOL /**< Enum value to represent a **NonTerminal** value. */

    };

    typedef struct AndExpr AndExpr; 
    
    AndExpr* new_AndExpr_Terminal( Terminal* term );
    AndExpr* new_AndExpr_NonTerminal( NonTerminal* nterm );

    AndExpr* append_ToAndExpr_Terminal( AndExpr* expr, Terminal* term );
    AndExpr* append_ToAndExpr_NonTerminal( AndExpr* expr, NonTerminal* nterm );
    
    unsigned int getAndExpr_id( AndExpr* expr );
    enum SymbolType getAndExpr_type( AndExpr* expr, int i );
    Terminal* getAndExpr_term( AndExpr* expr, int i );
    NonTerminal* getAndExpr_nterm( AndExpr* expr, int i );
    int getAndExpr_length( AndExpr* expr );
    
    void apply_ToAndExpr( AndExpr* expr, void (*applyToTerm) (), void (*applyToNTerm) () );

    void printAndExpr( AndExpr* AndExpression );
    void build_Graphviz_AndExpr( AndExpr* expr, FILE* fp );

    void freeAndExpr(AndExpr* AndExpression);

    /** @} */

#endif
