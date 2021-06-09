
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

    typedef struct Binding Binding;
    
    Binding* new_Binding( NonTerminal* nterm, OrExpr* OrExpression );
    
    unsigned int getBinding_id( Binding* b );

    void freeBinding( Binding* binding );
    void printBinding( Binding* b );
    void buildBindingNode( Binding* b, FILE* fp );

    /** @} */

#endif
