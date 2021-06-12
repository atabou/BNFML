
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

    /**
     * @struct **OrExpr**
     * @brief struct to define a parsed **OrExpr** value in BNFML
     * 
     */
    struct OrExpr {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        AndExpr** branches; /**< An array of pointers to **AndExpr** objects.*/
        int n; /** An integer representing the number of elements in AndExpression. */

        // Getters
        unsigned int (*getID)(OrExpr* this);
        AndExpr** (*getBranches)( OrExpr* this );
        int (*length)( OrExpr* this );
        
        //Methods
        void (*print)(OrExpr* this);
        void (*toGraphviz)(OrExpr* this, FILE* fp);
        void (*append)( OrExpr* this, AndExpr* AndExpression );

        // Destructor
        void (*destruct)(OrExpr* this);

    };
    
    OrExpr* new_OrExpr( AndExpr* expr );

    /** @} */

#endif
