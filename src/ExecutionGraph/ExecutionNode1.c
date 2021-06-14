

#include <stdlib.h>

#include "ExecutionGraph/ExecutionNode.h"
#include "Common.h"

unsigned int id_GetExecutionNode( ExecutionNode* this );

void toGraphviz_ExecutionNode( ExecutionNode* this );
void destruct_ExecutionNode( ExecutionNode* this );


ExecutionNode* new_ExecutionNode(  ) {

    ExecutionNode* node = (ExecutionNode*) malloc( sizeof(ExecutionNode) );

    node->id = ExecutionID_Generator++;

    node->getID = id_GetExecutionNode;

}

unsigned int id_GetExecutionNode( ExecutionNode* this ) {

    return this->id;

}