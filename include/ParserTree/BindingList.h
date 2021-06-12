
/**
 * 
 * @file ParserTree.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef BINDIN_LIST_H
    
    #define BINDIN_LIST_H

    #include <stdlib.h>
    #include "Binding.h"

    typedef struct BindingList BindingList;


    /**
     * \addtogroup BindingList
     * @{
     */

    /**
     * @struct **BindingList**
     * @brief struct to define a parsed **BindingList** value in BNFML
     * 
     */
    struct BindingList {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        Binding** branches;
        int n;
        
        unsigned int (*getID)(BindingList* this);
        
        void (*append)(BindingList* this, Binding* bind);
        void (*print)(BindingList* this);
        void (*toGraphviz)(BindingList* this, FILE* fp);

        Binding* (*search)( BindingList* this, char* nterm_name );
        Binding* (*allElementsUnique)( BindingList* this );

        void (*destruct)(BindingList* this);


    }; 
    
    BindingList* new_BindingList( Binding* b );
    

    /** @} */

#endif
