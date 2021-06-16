
#ifndef OR_NODE_H

    #define OR_NODE_H

    typedef struct OrNode OrNode;

    #include "ExecutionNode.h"

    typedef struct OrNode OrNode;

    struct OrNode {

        ExecutionNode super;

        unsigned int (*getID)( OrNode* this );
        int (*getVisited)( OrNode* this );

        void (*toGraphviz)( OrNode* this, FILE* fp );
        void (*destruct)( OrNode* this );
        enum NodeType (*getDynamicType)( );


    };

    OrNode* new_OrNode( ExecutionNode* parent );

#endif