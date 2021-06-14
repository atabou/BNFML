

#ifndef AND_NODE_H

    #define AND_NODE_H

    #include "ExecutionNode.h"

    typedef struct AndNode AndNode;

    struct AndNode {

        ExecutionNode node;

        unsigned int (*getID)( AndNode* this );

        void (*toGraphviz)( AndNode* this );
        void (*destruct)( AndNode* this );


    };

    ExecutionNode* new_AndNode(  );

#endif