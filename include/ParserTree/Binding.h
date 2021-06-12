
/**
 * 
 * @file Binding.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition for the **Binding** functionality.
 * @bug No known bugs.
 */

#ifndef BINDING_H
    
    #define BINDING_H

    #include <stdlib.h>
    #include "NonTerminal.h"
    #include "OrExpr.h"

    /**
     * \addtogroup Binding
     * @{
     */

    typedef struct private_Binding private_Binding;
    typedef struct Binding Binding;

    /**
     * @struct **Binding**
     * @brief struct to define a parsed **Binding** value in BNFML
     * 
     */
    struct Binding {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
        OrExpr* OrExpression; /**< A pointer to a **OrExpr** object.*/

        unsigned int (*getID)( Binding* bind );
        NonTerminal* (*getNonTerminal)( Binding* bind );
        OrExpr* (*getOrExpr)( Binding* bind );
        
        void (*print)( Binding* bind );
        void (*toGraphviz)( Binding* bind, FILE* fp );

        void (*destruct)( Binding* bind );

        private_Binding* private;


    }; 
    
    Binding* new_Binding( NonTerminal* nterm, OrExpr* OrExpression );

    /** @} */

#endif
