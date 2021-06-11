
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

    #include "Symbol.h"

    /**
     * \addtogroup AndExpression
     * @{
     */

    typedef struct AndExpr AndExpr; 

    /**
     * @struct **AndExpr**
     * @brief struct to define a parsed **AndExpr** value in BNFML
     * 
     */
    struct AndExpr { // TODO AndExpression does not need to be a linked list.

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        Symbol** branches; /**< Array of pointers to **Symbol** objects. */
        int n; /**< Integer representing the number of elements in the array */

        // Getters
        unsigned int (*getID)(AndExpr* this);
        Symbol** (*getBranches)( AndExpr* this );
        int (*length)( AndExpr* this );
        
        //Methods
        void (*print)(AndExpr* this);
        void (*toGraphviz)(AndExpr* this, FILE* fp);
        void (*append)( AndExpr* this, Symbol* sym );

        // Destructor
        void (*destruct)(AndExpr* this);
        
    };
    
    AndExpr* new_AndExpr( Symbol* sym );

    
    // void apply_ToAndExpr( AndExpr* expr, void (*applyToTerm) (), void (*applyToNTerm) () );

    /** @} */

#endif
