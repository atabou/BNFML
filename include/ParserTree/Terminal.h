
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

    /**
     * \addtogroup Terminal
     * @{
     */
    
    typedef struct Terminal Terminal;

    Terminal* new_Terminal( char* value );

    unsigned int getTerminal_id( Terminal* term );
    char* getTerminal_value( Terminal* term );
    
    void freeTerminal(Terminal* term);
    void printTerminal( Terminal* term );
    void build_Graphviz_Terminal( Terminal* term, FILE* fp );

    /** @} */

#endif
