#include <stdio.h>
#include <stdlib.h>

#include "../include/BNF.h"

struct BindingList {

    unsigned int id;
    BindingList* prevBindings;
    Binding* binding;

};

BindingList* createBindingListFromBinding( Binding* b ) {

    BindingList* r = (BindingList*) malloc( sizeof(BindingList) );
    
    r->id = idGenerator++;
    r->prevBindings = NULL;
    r->binding = b;

    return r;

}

BindingList* appendBinding( BindingList* lst, Binding* b ) {

    BindingList* r = (BindingList*) malloc( sizeof(BindingList) );
    r->id = idGenerator++;
    r->prevBindings = lst;
    r->binding = b;
    
}

void freeBindingList(BindingList* bindingList) {

    freeBinding( bindingList->binding );
    free( bindingList->binding );
    bindingList->binding = NULL;

    if( bindingList->prevBindings != NULL ) {
        freeBindingList( bindingList->prevBindings );
    }

    free( bindingList->prevBindings );
    bindingList->prevBindings = NULL;

    free(bindingList);

}