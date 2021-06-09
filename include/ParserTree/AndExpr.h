
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

    typedef struct AndExpr AndExpr;

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

        TERM, /**< Enum value to reprsent a **Terminal** value. */
        NONTERM /**< Enum value to represent a **NonTerminal** value. */

    };

    /**
     * @struct **AndExpr**
     * @brief struct to define a parsed **AndExpr** value in BNFML
     * 
     */
    struct AndExpr { // TODO AndExpression does not need to be a linked list.

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        AndExpr* prevAndExpr; /**< A pointer to an **AndExpr** object.*/
        enum SymbolType type; /**< Enum **SymbolType** used to determine the type of symbol this object contains */
        union {
            NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
            Terminal* term; /**< A pointer to a **Terminal** object.*/
        };

    }; 
    
    AndExpr* createTerminalAndExpr( Terminal* term );
    AndExpr* createNonTerminalAndExpr( NonTerminal* nterm );

    AndExpr* appendTerminal( AndExpr* lst, Terminal* term );
    AndExpr* appendNonTerminal( AndExpr* lst, NonTerminal* nterm );
    
    void freeAndExpr(AndExpr* AndExpression);
    void printAndExpr( AndExpr* AndExpression );
    void buildAndExprNode( AndExpr* AndExpression, FILE* fp );

    /** @} */

#endif
