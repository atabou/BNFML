

/**
 * 
 * @file ExecutionTree.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create an ExecutionTree.
 * @bug No known bugs.
 */

#ifndef EXECUTION_TREE
    
    #define EXECUTION_TREE

    #include <stdlib.h>
    #include "ParserTree.h"

    typedef struct ExecutionNode ExecutionNode;

    /**
     * \addtogroup ExecutionNode
     * @{
     */

    /**
     * @enum ExecutionNodeType
     * @brief Enum to represent the types an **ExecutionNode** can take.
     * 
     */
    enum ExecutionNodeType {
        AND_NODE,
        OR_NODE,
        TERMINAL_NODE,
        NON_TERMINAL_NODE
    };

    /**
     * @struct **ExecutionNode**
     * @brief struct to define an **ExecutionNode** used when processing a parsed **BindingList**
     * 
     */
    struct ExecutionNode {

        unsigned int id; /**< Global ID of the object. see: executionTreeIDGenerator*/
        enum ExecutionNodeType NodeType; /** The type of execution node this object represents. */
        union {

            char* nterm; /**< A string to represent the name of a NON_TERMINAL_NODE */
            char* term;  /**< A string to Represent the value of a TERMINAL_NODE */

        };

    }; 
    


    ExecutionNode* createTerminalExecutionNode( Terminal* term );
    ExecutionNode* createNonTerminalExecutionNode( NonTerminal* nterm );
    ExecutionNode* createAndExecutionNode( );
    ExecutionNode* createOrExecutionNode( );

    void freeExecutionNode(ExecutionNode* leaf);
    

    /** @} */



    /**
     * \addtogroup ExecutionTree
     * @{
     */

    typedef struct ExecutionTree ExecutionTree; 
    
    ExecutionTree* buildExecutionTree( BindingList* lst );

    void freeExecutionTree(ExecutionTree* tree);
    
    /** @} */

    extern unsigned int executionTreeIDGenerator;

#endif
