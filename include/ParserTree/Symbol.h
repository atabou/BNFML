
#ifndef SYMBOL_H

    #define SYMBOL_H

    /**
     * @enum SymbolType
     * @brief Enum to represent the types a symbol can be.
     * 
     */

    #include "Terminal.h"
    #include "NonTerminal.h"

    enum SymbolType {

        TERMINAL_SYMBOL, /**< Enum value to reprsent a **Terminal** value. */
        NON_TERMINAL_SYMBOL /**< Enum value to represent a **NonTerminal** value. */

    };

    typedef struct Symbol Symbol;

    struct Symbol {

        enum SymbolType type; /**< Enum **SymbolType** used to determine the type of symbol this object contains */

        union {
            NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
            Terminal* term; /**< A pointer to a **Terminal** object.*/
        };

        enum SymbolType (*getType)( Symbol* this );
        Terminal* (*getTerminal)( Symbol* this );
        NonTerminal* (*getNonTerminal)( Symbol* this );

    };
    
    Symbol* new_Symbol_Terminal( Terminal* term );
    Symbol* new_Symbol_NonTerminal( NonTerminal* nterm );
    

#endif