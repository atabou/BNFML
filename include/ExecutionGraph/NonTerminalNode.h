
#ifndef NON_TERMINAL_NODE_H

    #define NON_TERMINAL_NODE_H

    #include "ExecutionNode.h"

    typedef struct NonTerminalNode NonTerminalNode;

    struct NonTerminalNode {

        ExecutionNode super;

        char* value;

        unsigned int (*getID)( NonTerminalNode* this );
        char* (*getValue)( NonTerminalNode* this );

        void (*toGraphviz)( NonTerminalNode* this, FILE* fp );
        void (*destruct)( NonTerminalNode* this );
        enum NodeType (*getDynamicType)( );


    };

    NonTerminalNode* new_NonTerminalNode( char* value );


#endif