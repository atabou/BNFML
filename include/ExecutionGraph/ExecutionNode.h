

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
        
        ExecutionNode** branches;
        int n;

        ExecutionNode* parent;
        int visited;

        unsigned int (*getID)( ExecutionNode* this );
        unsigned int (*getVisited)( ExecutionNode* this );

        // Abstract
        void (*append)( ExecutionNode* this, ExecutionNode* child );
        void (*toGraphviz)( ExecutionNode* this, int counter, FILE* fp );
        void (*destruct)( ExecutionNode* this );
        enum NodeType (*getDynamicType)( );

       
    };

    ExecutionNode* new_ExecutionNode( ExecutionNode* parent );


#endif