

#ifndef EXECUTION_NODE_H

    #define EXECUTION_NODE_H

    #include <stdio.h>

    enum NodeType {

        TERMINAL_NODE,
        NON_TERMINAL_NODE,
        AND_NODE,
        OR_NODE

    };

    typedef struct ExecutionNode ExecutionNode;
    
    struct ExecutionNode {

        unsigned int id;

        unsigned int (*getID)( ExecutionNode* this );

        // Abstract
        void (*toGraphviz)( ExecutionNode* this, FILE* fp );
        void (*destruct)( ExecutionNode* this );
        enum NodeType (*getDynamicType)( );

       
    };

    ExecutionNode* new_ExecutionNode();


#endif