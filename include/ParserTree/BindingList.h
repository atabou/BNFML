
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
    
    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding* b );
    
    void freeBindingList( BindingList* bindingList );
    void printBindingList( BindingList* lst );
    void buildBindingListNode( BindingList* lst, FILE* fp );
    Binding* verifyUniquenessOfBindings( BindingList* lst );
    Binding* searchForBinding( BindingList* lst, char* nterm );

    /** @} */

#endif
