
#ifndef NON_TERMINAL_NODE_H

    #define NON_TERMINAL_NODE_H

    #include "ExecutionNode.h"

    #include "ParserTree/NonTerminal.h"
    #include "ParserTree/OrExpr.h"
    #include "ParserTree/Binding.h"
    #include "ParserTree/BindingList.h"

    typedef struct NonTerminalNode NonTerminalNode;

    struct NonTerminalNode {

        ExecutionNode super;

        char* value;

        unsigned int (*getID)( NonTerminalNode* this );
        char* (*getValue)( NonTerminalNode* this );
        int (*getVisited)( NonTerminalNode* this );

        void (*toGraphviz)( NonTerminalNode* this, FILE* fp );
        void (*destruct)( NonTerminalNode* this );
        enum NodeType (*getDynamicType)( );

        void (*explore)( OrExpr* expr, ExecutionNode* parent, BindingList* lst );


    };

    NonTerminalNode* new_NonTerminalNode( char* value, ExecutionNode* parent );


#endif