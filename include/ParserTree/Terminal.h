
/**
 * 
 * @file Terminal.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the **Terminal** objects.
 * @bug No known bugs.
 */

#ifndef TERMINAL_H
    
    #define TERMINAL_H

    #include <stdio.h>
    #include "Common.h"

    /**
     * \addtogroup Terminal
     * @{
     */
    
    typedef struct Terminal Terminal;

    /**
     * @struct **Terminal**
     * @brief struct to define a parsed **Terminal** value in BNFML
     * 
     */
    struct Terminal {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        char* value; /**< A regular expression representing the values a terminal can take.*/

        CommonInterface* fn;

    };

    Terminal* new_Terminal( char* value );

    char* getTerminal_value( Terminal* term );
    
    /** @} */

#endif
