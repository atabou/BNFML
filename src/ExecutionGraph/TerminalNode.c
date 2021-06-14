

#include <stdlib.h>
#include <string.h>

#include "ExecutionGraph/TerminalNode.h"

unsigned int id_GetTerminalNode( TerminalNode* this );

void toGraphviz_TerminalNode( TerminalNode* this );
void toGraphviz_Dispatch( ExecutionNode* super );


void destruct_TerminalNode( TerminalNode* this );
void destruct_Dispatch( ExecutionNode* super );

ExecutionNode* new_TerminalNode( char* value ) {

    TerminalNode* term = (TerminalNode*) malloc( sizeof(TerminalNode) );

    term->super = *( new_ExecutionNode() );
    term->value = strdup( value );

    term->getID = id_GetTerminalNode;

    term->toGraphviz = toGraphviz_TerminalNode;
    term->super.toGraphviz = toGraphviz_Dispatch;
    
    term->destruct = destruct_TerminalNode;
    term->super.destruct = destruct_Dispatch;



}

unsigned int id_GetTerminalNode( TerminalNode* this ) {
    return this->super.getID( (TerminalNode*) this );
}

void toGraphviz_TerminalNode( TerminalNode* this ) {

}

void toGraphviz_Dispatch( ExecutionNode* super ) {

    TerminalNode* this = (TerminalNode*) super;
    this->toGraphviz( this );

}


void destruct_TerminalNode( TerminalNode* this );

void destruct_Dispatch( ExecutionNode* super ) {

    TerminalNode* this = (TerminalNode*) super;
    this->destruct( this );

}