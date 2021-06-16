

/**
 * 
 * @file ExecutionGraph.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create an ExecutionGraph.
 * @bug No known bugs.
 */

#ifndef EXECUTION_GRAPH
    
    #define EXECUTION_GRAPH

    #include <stdlib.h>
    #include "ParserTree.h"
    #include "ExecutionNode.h"


    /**
     * \addtogroup ExecutionGraph
     * @{
     */

    typedef struct ExecutionGraph ExecutionGraph; 
    
    struct ExecutionGraph {

        ExecutionNode* Node;
        int visit_counter;

        void (*toGraphviz)( ExecutionGraph* G, FILE* fp );
        void (*destruct)( ExecutionGraph* G );

    };

    ExecutionGraph* new_ExecutionGraph( BindingList* lst );
    void buildGraphvizExecutionGraphRepresentation( ExecutionGraph* G, FILE* fp );

    void freeExecutionGraph(ExecutionGraph* tree);
    
    /** @} */

#endif
