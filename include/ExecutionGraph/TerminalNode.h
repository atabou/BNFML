
#ifndef TERMINAL_NODE_H

    #define TERMINAL_NODE_H

    #include "ExecutionNode.h"

    typedef struct TerminalNode TerminalNode;

    struct TerminalNode {

        ExecutionNode super;

        char* value;

        unsigned int (*getID)( TerminalNode* this );

        void (*toGraphviz)( TerminalNode* this, FILE* fp );
        void (*destruct)( TerminalNode* this );
        enum NodeType (*getDynamicType)( );


    };

    TerminalNode* new_TerminalNode( char* value );


#endif