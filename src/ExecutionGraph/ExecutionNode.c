

#include <stdlib.h>
#include <stdio.h>

#include "ExecutionGraph/ExecutionNode.h"
#include "Common.h"

unsigned int id_GetExecutionNode( ExecutionNode* this );

ExecutionNode* new_ExecutionNode(  ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = ExecutionID_Generator++;

    node->getID = id_GetExecutionNode;

    return node;

}

unsigned int id_GetExecutionNode( ExecutionNode* this ) {

    return this->id;

}