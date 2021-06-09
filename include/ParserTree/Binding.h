
/**
 * 
 * @file ParserTree.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef BINDING_H
    
    #define BINDING_H

    #include <stdlib.h>
    #include "NonTerminal.h"
    #include "OrExpr.h"

    typedef struct Binding Binding;

    /**
     * \addtogroup Binding
     * @{
     */

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
    
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );
    
    void freeBinding( Binding* binding );
    void printBinding( Binding* b );
    void buildBindingNode( Binding* b, FILE* fp );

    /** @} */

#endif
