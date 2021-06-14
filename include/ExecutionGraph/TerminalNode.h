
#ifndef TERMINAL_NODE_H

    #define TERMINAL_NODE_H

    #include "ExecutionNode.h"

    typedef struct TerminalNode TerminalNode;

    struct TerminalNode {

        ExecutionNode super;

        char* value;

        unsigned int (*getID)( TerminalNode* this );

        void (*toGraphviz)( TerminalNode* this );
        void (*destruct)( TerminalNode* this );


    };

    ExecutionNode* new_TerminalNode( char* value );


#endif