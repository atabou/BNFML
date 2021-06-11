
/**
 * 
 * @file NonTerminal.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create a **NonTerminal** object, as well as the functions related to it.
 * @bug No known bugs.
 */

#ifndef NON_TERMINAL_H
    
    #define NON_TERMINAL_H

    #include "Symbol.h"

    /**
     * \addtogroup NonTerminal
     * @{
     */

    typedef struct NonTerminal NonTerminal;

    /**
     * @struct **NonTerminal**
     * @brief struct to define a parsed **NonTerminal** object in BNFML
     * 
     */
    struct NonTerminal {

        Symbol super;

        /* Fields */
        char* name;

        /* Getters */
        char* (*getName)( NonTerminal* term );

        /* Inherited */
        unsigned int (*getID)( NonTerminal* this );

        /* Must Implement */
        void (*print)( NonTerminal* this );
        void (*build_Graphviz)( NonTerminal* this, FILE* fp );
        void (*destruct)( NonTerminal* this );
        enum SymbolType (*getDynamicType)(  );




    };

    NonTerminal* new_NonTerminal( char* name );

    /** @} */

#endif
