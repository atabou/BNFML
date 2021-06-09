
/**
 * 
 * @file NonTerminal.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef NON_TERMINAL_H
    
    #define NON_TERMINAL_H

    #include <stdio.h>

    typedef struct NonTerminal NonTerminal;

    
    /**
     * \addtogroup NonTerminal
     * @{
     */

    /**
     * @struct **NonTerminal**
     * @brief struct to define a parsed **NonTerminal** object in BNFML
     * 
     */
    struct NonTerminal {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        char* Name; /**< A string representing the name of a non-terminal.*/

    }; 

    
    NonTerminal* createNonTerminal( char* Name );

    void freeNonTerminal( NonTerminal* nterm );
    void printNonTerminal( NonTerminal* nterm );
    void buildNonTerminalNode( NonTerminal* nterm, FILE* fp );

    /** @} */

#endif
