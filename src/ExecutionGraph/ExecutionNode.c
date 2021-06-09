
/**
 * 
 * @file ExecutionNode.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Implementation file for the functions related to the **ExecutionNode** struct.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ExecutionGraph.h"
#include "ParserTree.h"

/**
 * @brief Constructor to create an **ExecutionNode** object for a Terminal node.
 * 
 * @param term A pointer to a **Terminal** Object.
 * @return ExecutionNode* A pointer to a newly created **ExecutionNode** object.
 */
ExecutionNode* createTerminalExecutionNode( Terminal* term ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = executionTreeIDGenerator++;
    node->NodeType = TERMINAL_NODE;
    node->term = strdup(term->regex);

    return node;

}

/**
 * @brief Constructor to create an **ExecutionNode** object for a Non-Terminal Node.
 * 
 * @param nterm A pointer to a **NonTerminal** Object.
 * @return ExecutionNode* A pointer to a newly created **ExecutionNode** object.
 */
ExecutionNode* createNonTerminalExecutionNode( NonTerminal* nterm ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = executionTreeIDGenerator++;
    node->NodeType = NON_TERMINAL_NODE;
    node->nterm = strdup(nterm->Name);

    return node;

}

/**
 * @brief Constructor to create an **ExecutionNode** object for an OR node.
 * 
 * @return ExecutionNode* A pointer to a newly created **ExecutionNode** object.
 */
ExecutionNode* createAndExecutionNode( ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = executionTreeIDGenerator++;
    node->NodeType = AND_NODE;
    
    return node;

}

/**
 * @brief Constructor to create an **ExecutionNode** object for an AND node.
 * 
 * @return ExecutionNode* A pointer to a newly created **ExecutionNode** object.
 */
ExecutionNode* createOrExecutionNode( ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = executionTreeIDGenerator++;
    node->NodeType = OR_NODE;
    
    return node;

}

void buildGraphvizExecutionNodeRepresentation( ExecutionNode* node, FILE* fp ) {

    if( node->NodeType == TERMINAL_NODE ) {

        fprintf( fp, "%u [label=\"%s\"];\n", node->id, node->term );

    } else if( node->NodeType == NON_TERMINAL_NODE ) {

        fprintf( fp, "%u [label=\"%s\"];\n", node->id, node->nterm );

    } else if( node->NodeType == AND_NODE ) {

        fprintf( fp, "%u [label=\"AND\"];\n", node->id);

    } else if( node->NodeType == OR_NODE ) {

        fprintf( fp, "%u [label=\"OR\"];\n", node->id );

    }

}

/**
 * @brief Destructor for an **ExecutionNode** object.
 * 
 * @param node A pointer to the **ExecutionNode** object you want to destruct.
 */
void freeExecutionNode(ExecutionNode* node) {

    if( node->NodeType == NON_TERMINAL_NODE ) {
        free( node->nterm );
        node->nterm = NULL;
    } else if ( node->NodeType == TERMINAL_NODE ) {
        free( node->term );
        node->nterm = NULL;
    }

}
    

