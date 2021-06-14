
#ifndef OR_NODE_H

    #define OR_NODE_H

    typedef struct OrNode OrNode;

    #include "ExecutionNode.h"

    typedef struct OrNode OrNode;

    struct OrNode {

        ExecutionNode node;

        unsigned int (*getID)( OrNode* this );

        void (*toGraphviz)( OrNode* this );
        void (*destruct)( OrNode* this );


    };

    ExecutionNode* new_OrNode(  );

#endif