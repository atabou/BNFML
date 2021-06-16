

#include <stdlib.h>
#include <stdio.h>

#include "ExecutionGraph/ExecutionNode.h"
#include "Common.h"

unsigned int id_GetExecutionNode( ExecutionNode* this );
int getVisited( ExecutionNode* this );

ExecutionNode* new_ExecutionNode( ExecutionNode* parent ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = ExecutionID_Generator++;
    node->branches = NULL;
    node->n = 0;
    node->parent = parent;
    node->visited = 0;

    node->getID = id_GetExecutionNode;

    return node;

}

unsigned int id_GetExecutionNode( ExecutionNode* this ) {

    return this->id;

}

int getVisited ( ExecutionNode* this ) {

    return this->visited;

}