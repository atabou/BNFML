

#ifndef AND_NODE_H

    #define AND_NODE_H

    #include "ExecutionNode.h"

    typedef struct AndNode AndNode;

    struct AndNode {

        ExecutionNode super;

        unsigned int (*getID)( AndNode* this );

        void (*toGraphviz)( AndNode* this, FILE* fp );
        void (*destruct)( AndNode* this );
        enum NodeType (*getDynamicType)( );


    };

    AndNode* new_AndNode(  );

#endif