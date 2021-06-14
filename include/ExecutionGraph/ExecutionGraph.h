

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


    /**
     * \addtogroup ExecutionGraph
     * @{
     */

    typedef struct ExecutionGraph ExecutionGraph; 
    
    ExecutionGraph* buildExecutionGraph( BindingList* lst );
    void buildGraphvizExecutionGraphRepresentation( ExecutionGraph* G, FILE* fp );

    void freeExecutionGraph(ExecutionGraph* tree);
    
    /** @} */

#endif
