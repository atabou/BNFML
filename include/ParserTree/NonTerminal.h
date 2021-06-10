
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
    #include "Common.h"
    
    /**
     * \addtogroup NonTerminal
     * @{
     */

    /**
     * @struct **NonTerminal**
     * @brief struct to define a parsed **NonTerminal** object in BNFML
     * 
     */
    typedef struct NonTerminal {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        char* name; /**< A string representing the name of a non-terminal.*/

        CommonInterface* fn;

    } NonTerminal;


    NonTerminal* new_NonTerminal( char* name );

    char* getNonTerminal_name( NonTerminal* term );

    /** @} */

#endif
