
#ifndef BINDINGLIST
    
    #define BINDINGLIST

    #include "BNF.h"

    typedef struct BindingList BindingList;

    /* Constructor Definitions */

    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding b );

#endif