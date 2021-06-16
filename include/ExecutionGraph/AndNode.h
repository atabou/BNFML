

#ifndef AND_NODE_H

    #define AND_NODE_H

    #include "ExecutionNode.h"

    typedef struct AndNode AndNode;

    struct AndNode {

        ExecutionNode super;

        unsigned int (*getID)( AndNode* this );
        int (*getVisited)( AndNode* this );

        void (*toGraphviz)( AndNode* this, FILE* fp );
        void (*destruct)( AndNode* this );
        enum NodeType (*getDynamicType)( );


    };

    AndNode* new_AndNode( ExecutionNode* parent );

#endif