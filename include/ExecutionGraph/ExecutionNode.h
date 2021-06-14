

#ifndef EXECUTION_NODE_H

    #define EXECUTION_NODE_H

    #include <stdio.h>

    typedef struct ExecutionNode ExecutionNode;
    
    struct ExecutionNode {

        unsigned int id;

        unsigned int (*getID)( ExecutionNode* this );

        // Abstract
        void (*toGraphviz)( ExecutionNode* this );
        void (*destruct)( ExecutionNode* this );

       
    };

    ExecutionNode* new_ExecutionNode();


#endif