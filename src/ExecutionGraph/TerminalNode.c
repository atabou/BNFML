

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ExecutionGraph/TerminalNode.h"

unsigned int id_GetTerminalNode( TerminalNode* this );
int visited_GetTerminalNode( TerminalNode* this );

enum NodeType dynamicType_GetTerminalNode();

void toGraphviz_TerminalNode( TerminalNode* this, int counter, FILE* fp );
void toGraphviz_Dispatch( ExecutionNode* super, FILE* fp );

void destruct_TerminalNode( TerminalNode* this );
void destruct_Dispatch( ExecutionNode* super );

TerminalNode* new_TerminalNode( char* value, ExecutionNode* parent ) {

    TerminalNode* term = (TerminalNode*) malloc( sizeof(TerminalNode) );

    term->super = *(new_ExecutionNode( parent ));
    term->value = strdup( value );

    term->getID = id_GetTerminalNode;
    term->getVisited = visited_GetTerminalNode;

    term->getDynamicType = dynamicType_GetTerminalNode;
    term->super.getDynamicType = dynamicType_GetTerminalNode;

    term->toGraphviz = toGraphviz_TerminalNode;
    term->super.toGraphviz = toGraphviz_Dispatch;
    
    term->destruct = destruct_TerminalNode;
    term->super.destruct = destruct_Dispatch;

    return term;

}


unsigned int id_GetTerminalNode( TerminalNode* this ) {

    return this->super.getID( (ExecutionNode*) this );

}

int visited_GetTerminalNode( TerminalNode* this ) {

    return this->super.getVisited( this );

}



enum NodeType dynamicType_GetTerminalNode() {

    return TERMINAL_NODE;

}

void toGraphviz_TerminalNode( TerminalNode* this, int counter, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), this->value );
    
}

void toGraphviz_Dispatch( ExecutionNode* super, FILE* fp ) {

    TerminalNode* this = (TerminalNode*) super;
    this->toGraphviz( this, fp );

}


void destruct_TerminalNode( TerminalNode* this ) {

    // TODO find a way to connect to parent destructor
    free(this->value);
    this->value = NULL;

    // TODO does not work
    free( &(this->super) );
    
}

void destruct_Dispatch( ExecutionNode* super ) {

    TerminalNode* this = (TerminalNode*) super;
    this->destruct( this );

}