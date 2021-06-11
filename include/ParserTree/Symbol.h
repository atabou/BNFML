
#ifndef SYMBOL_H

    #define SYMBOL_H

    #include <stdio.h>

    #include "Common.h"

    typedef struct Symbol Symbol;

    struct Symbol {

        unsigned int id;

        /* Getters */
        unsigned int (*getID)( Symbol* id );

        /* Abstract Methods */
        void (*print)( Symbol* this );
        void (*build_Graphviz)( Symbol* this, FILE* fp );
        void (*destruct)( Symbol* this );
        enum SymbolType (*getDynamicType)(  );

    };
    
    Symbol* new_Symbol( );
    

#endif