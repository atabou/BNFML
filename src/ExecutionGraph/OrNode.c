

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ExecutionGraph/OrNode.h"

unsigned int id_GetOrNode( OrNode* this );

enum NodeType dynamicType_GetOrNode();

void toGraphviz_OrNode( OrNode* this, FILE* fp );
void toGraphviz_Dispatch_OrNode( ExecutionNode* super, FILE* fp );

void destruct_OrNode( OrNode* this );
void destruct_Dispatch_OrNode( ExecutionNode* super );

OrNode* new_OrNode( char* value ) {

    OrNode* o = (OrNode*) malloc( sizeof(OrNode) );

    o->super = *(new_ExecutionNode());
    
    o->getID = id_GetOrNode;

    o->getDynamicType = dynamicType_GetOrNode;
    o->super.getDynamicType = dynamicType_GetOrNode;

    o->toGraphviz = toGraphviz_OrNode;
    o->super.toGraphviz = toGraphviz_Dispatch_OrNode;

    o->destruct = destruct_OrNode;
    o->super.destruct = destruct_Dispatch_OrNode;

    return o;

}



unsigned int id_GetOrNode( OrNode* this ) {

    return this->super.getID( (ExecutionNode*) this );

}

enum NodeType dynamicType_GetOrNode() {
    return OR_NODE;
}

void toGraphviz_OrNode( OrNode* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), "OR" );
    
}

void toGraphviz_Dispatch_OrNode( ExecutionNode* super, FILE* fp ) {

    OrNode* this = (OrNode*) super;
    return this->toGraphviz( this, fp );

}


void destruct_OrNode( OrNode* this ) {

    // TODO find a way to connect to parent destructor.

    // TODO does not work
    free( &(this->super) );
    
}

void destruct_Dispatch_OrNode( ExecutionNode* super ) {

    OrNode* this = (OrNode*) super;
    this->destruct( this );

}