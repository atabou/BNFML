
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
    #include "Symbol.h"
    #include "Common.h"

    /**
     * \addtogroup Terminal
     * @{
     */
    
    typedef struct Terminal_private Terminal_private;
    typedef struct Terminal Terminal;

    struct Terminal {

        Symbol super;

        /* Fields */
        char* value; /**< A regular expression representing the values a terminal can take.*/
        
        /* Getters */
        char* (*getValue)( Terminal* term );

        /* Inherited */
        unsigned int (*getID)( Terminal* this );

        /* Must Implement */
        void (*print)( Terminal* this );
        void (*build_Graphviz)( Terminal* this, FILE* fp );
        void (*destruct)( Terminal* this );
        enum SymbolType (*getDynamicType)(  );

    };

    Terminal* new_Terminal( char* value );
    
    /** @} */

#endif
