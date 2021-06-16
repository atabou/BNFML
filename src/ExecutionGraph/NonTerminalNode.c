

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ExecutionGraph/NonTerminalNode.h"
#include "ExecutionGraph/AndNode.h"

#include "ParserTree/NonTerminal.h"
#include "ParserTree/OrExpr.h"
#include "ParserTree/Binding.h"
#include "ParserTree/BindingList.h"

unsigned int id_GetNonTerminalNode( NonTerminalNode* this );
int visited_GetNonTerminalNode( NonTerminalNode* this );

char* value_GetNonTerminalNode( NonTerminalNode* this );

enum NodeType dynamicType_GetNonTerminalNode();

void toGraphviz_NonTerminalNode( NonTerminalNode* this, FILE* fp );
void toGraphviz_Dispatch_NonTerminalNode( ExecutionNode* super, FILE* fp );

void destruct_NonTerminalNode( NonTerminalNode* this );
void destruct_Dispatch_NonTerminalNode( ExecutionNode* super );

void explore_NonTerminalNode( OrExpr* expr, ExecutionNode* parent, BindingList* lst );
void explore_Dispatch_NonTerminalNode( OrExpr* expr, ExecutionNode* parent, BindingList* lst );


NonTerminalNode* new_NonTerminalNode( char* value, ExecutionNode* parent ) {

    NonTerminalNode* nterm = (NonTerminalNode*) malloc( sizeof(NonTerminalNode) );

    nterm->super = *(new_ExecutionNode( parent ));
    nterm->value = strdup( value );

    nterm->getID = id_GetNonTerminalNode;
    nterm->getVisited = visited_GetNonTerminalNode;

    nterm->getValue = value_GetNonTerminalNode;

    nterm->explore = explore_NonTerminalNode;
    nterm->explore = explore_Dispatch_NonTerminalNode;

    nterm->toGraphviz = toGraphviz_NonTerminalNode;
    nterm->super.toGraphviz = toGraphviz_Dispatch_NonTerminalNode;
    
    nterm->getDynamicType = dynamicType_GetNonTerminalNode;
    nterm->super.getDynamicType = dynamicType_GetNonTerminalNode;

    nterm->destruct = destruct_NonTerminalNode;
    nterm->super.destruct = destruct_Dispatch_NonTerminalNode;

    return nterm;

}

unsigned int id_GetNonTerminalNode( NonTerminalNode* this ) {

    return this->super.getID( (ExecutionNode*) this );

}


int visited_GetNonTerminalNode ( NonTerminalNode* this ) {

    return this->super.getVisited( (ExecutionNode*) this );

}


char* value_GetNonTerminalNode( NonTerminalNode* this ) {

    return this->value;

}


enum NodeType dynamicType_GetNonTerminalNode() {

    return NON_TERMINAL_NODE;

}

void explore_NonTerminalNode( OrExpr* expr, ExecutionNode* parent, BindingList* lst ) {

}

void explore_Dispatch_NonTerminalNode( OrExpr* expr, ExecutionNode* parent, BindingList* lst ) {



}

void toGraphviz_NonTerminalNode( NonTerminalNode* this, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), this->value );
    
}

void toGraphviz_Dispatch_NonTerminalNode( ExecutionNode* super, FILE* fp ) {

    NonTerminalNode* this = (NonTerminalNode*) super;
    this->toGraphviz( this, fp );

}


void destruct_NonTerminalNode( NonTerminalNode* this ) {

    // TODO find a way to connect to parent constructor

    free(this->value);
    this->value = NULL;

    // TODO cannot destruct
    free( &(this->super) );
    
}

void destruct_Dispatch_NonTerminalNode( ExecutionNode* super ) {

    NonTerminalNode* this = (NonTerminalNode*) super;
    this->destruct( this );

}