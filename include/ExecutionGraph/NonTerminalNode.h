
#ifndef NON_TERMINAL_NODE_H

    #define NON_TERMINAL_NODE_H

    #include "ExecutionNode.h"

    typedef struct NonTerminalNode NonTerminalNode;

    struct NonTerminalNode {

        ExecutionNode node;

        char* value;

        unsigned int (*getID)( NonTerminalNode* this );

        void (*toGraphviz)( NonTerminalNode* this );
        void (*destruct)( NonTerminalNode* this );


    };

    ExecutionNode* new_NonTerminalNode( char* value );


#endif