
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
        BindingList* prevBindings; /**< A pointer to a **BindingList** object.*/
        Binding* binding; /**< A pointer to a **Binding** object.*/

    }; 
    
    BindingList* new_BindingList( Binding* b );
    BindingList* append_ToBindingList_Binding( BindingList* lst, Binding* b );
    
    void printBindingList( BindingList* lst );
    void build_Graphviz_BindingList( BindingList* lst, FILE* fp );

    Binding* verifyUniquenessOfBindings( BindingList* lst );
    Binding* search_InBindignList( BindingList* lst, char* nterm );

    void freeBindingList( BindingList* bindingList );
    

    /** @} */

#endif
