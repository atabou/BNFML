/**
 * 
 * @file BindingList.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief C file containing implementations of the BindingList struct related functions
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ParserTree/BindingList.h"
#include "ParserTree/Binding.h"
#include "Common.h"

unsigned int id_GetBindingList(BindingList* this);

void append_BindingList(BindingList* this, Binding* bind);
void print_BindingList(BindingList* this);
void toGraphviz_BindingList(BindingList* this, FILE* fp);

Binding* search_BindingList( BindingList* this, char* nterm_name );
Binding* allElementsUnique_BindingList( BindingList* this );

void destruct_BindingList(BindingList* this);

BindingList* new_BindingList( Binding* b ) {

    BindingList* r = (BindingList*) malloc( sizeof(BindingList) );
    
    r->id = ParserID_Generator++;
    
    r->branches = (Binding**) malloc( sizeof(Binding*) );
    r->branches[0] = b;
    r->n = 1;

    r->getID = id_GetBindingList;

    r->append = append_BindingList;
    r->print = print_BindingList;
    r->toGraphviz = toGraphviz_BindingList;

    r->search = search_BindingList;
    r->allElementsUnique = allElementsUnique_BindingList;

    r->destruct = destruct_BindingList;

    return r;

}

unsigned int id_GetBindingList(BindingList* this) {

    return this->id;

}

void append_BindingList(BindingList* this, Binding* bind) {

    Binding** lst = (Binding**) malloc( sizeof(Binding*) * (this->n + 1) );

    for( int i=1; i<=this->n; i++ ) {
        lst[i] = this->branches[i-1];
    }

    lst[0] = bind;

    free( this->branches );
    
    this->branches = lst;
    this->n = this->n + 1;

}

void print_BindingList(BindingList* this) {

    printf( "\n----------------------------------------\n\n" );

    printf("Binding List:\n");
    printf("-------------\n");
    
    printf("\n");

    for( int i=0; i < this->n; i++ ) {
        
        this->branches[i]->print( this->branches[i] );
        printf("\n");

    }

    printf("\nEND\n");

    printf( "\n----------------------------------------\n\n" );

}

void toGraphviz_BindingList(BindingList* this, FILE* fp) {

    fprintf( fp, "%u [label=\"%s\"];\n", this->getID(this), "Binding List" );

    for( int i=0; i < this->n; i++ ) {

        Binding* bind = this->branches[i];
        fprintf( fp, "%u -> %u;\n", this->getID(this), bind->getID( bind ) );
        bind->toGraphviz(bind, fp);

    }

}

Binding* search_BindingList( BindingList* this, char* look_for ) {

    Binding* b = NULL;

    for( int i=0; i < this->n; i++ ) {

        NonTerminal* nterm = this->branches[i]->getNonTerminal( this->branches[i] );

        if( strcmp( nterm->getName(nterm), look_for ) == 0 ) {

            b = this->branches[i];
            break;

        }

    }

    return b;

}

Binding* allElementsUnique_BindingList( BindingList* this ) {

    Binding* b = NULL;

    for( int i=0; i < this->n - 1; i++ ) {
        
        for( int j=i+1; j < this->n; j++ ) {

            NonTerminal* term1 = this->branches[i]->getNonTerminal( this->branches[i] );
            NonTerminal* term2 = this->branches[j]->getNonTerminal( this->branches[j] );

            if( strcmp( term1->getName(term1), term2->getName(term2) ) == 0 ) {

                b = this->branches[j];
                break;

            }

        }

    }

    return b;


}

void destruct_BindingList(BindingList* this) {

    for( int i=0; i<this->n; i++ ) {
        
        this->branches[i]->destruct( this->branches[i] );
        free( this->branches[i] );
        this->branches[i] = NULL;

    }

    free( this->branches );
    this->branches = NULL;


}
