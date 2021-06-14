

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ExecutionGraph/AndNode.h"

unsigned int id_GetAndNode( AndNode* this );

enum NodeType dynamicType_GetAndNode();

void toGraphviz_AndNode( AndNode* this, FILE* fp );
void toGraphviz_Dispatch_AndNode( ExecutionNode* super, FILE* fp );

void destruct_AndNode( AndNode* this );
void destruct_Dispatch_AndNode( ExecutionNode* super );

AndNode* new_AndNode( char* value ) {

    AndNode* a = (AndNode*) malloc( sizeof(AndNode) );

    a->super = *new_ExecutionNode();
    
    a->getID = id_GetAndNode;

    a->getDynamicType = dynamicType_GetAndNode;
    a->super.getDynamicType = dynamicType_GetAndNode;

    a->toGraphviz = toGraphviz_AndNode;
    a->super.toGraphviz = toGraphviz_Dispatch_AndNode;
    
    a->destruct = destruct_AndNode;
    a->super.destruct = destruct_Dispatch_AndNode;

    return a;

}

unsigned int id_GetAndNode( AndNode* this ) {

    return this->super.getID( (ExecutionNode*) this );

}


enum NodeType dynamicType_GetAndNode(AndNode* this) {
    return AND_NODE;
}


void toGraphviz_AndNode( AndNode* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), "AND" );
    
}

void toGraphviz_Dispatch_AndNode( ExecutionNode* super, FILE* fp ) {

    AndNode* this = (AndNode*) super;
    this->toGraphviz( this, fp );

}


void destruct_AndNode( AndNode* this ) {

    // TODO find a way to connect to parent destructor

    // TODO This data is not being freed
    free( &(this->super) );
    
}

void destruct_Dispatch_AndNode( ExecutionNode* super ) {

    AndNode* this = (AndNode*) super;
    this->destruct( this );

}