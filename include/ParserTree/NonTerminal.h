
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

    #include <stdio.h>
    
    /**
     * \addtogroup NonTerminal
     * @{
     */

    /**
     * @struct **NonTerminal**
     * @brief struct to define a parsed **NonTerminal** object in BNFML
     * 
     */

    typedef struct NonTerminal NonTerminal;

    NonTerminal* new_NonTerminal( char* name );

    int getNonTerminal_id( NonTerminal* nterm );
    char* getNonTerminal_name( NonTerminal* term );

    void freeNonTerminal( NonTerminal* nterm );
    void printNonTerminal( NonTerminal* nterm );
    void build_Graphviz_NonTerminal( NonTerminal* nterm, FILE* fp );

    /** @} */

#endif
