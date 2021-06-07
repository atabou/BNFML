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

#include "ParserTree.h"

/**
 * @brief Constructor to create a **Binding** object.
 * 
 * @param b A pointer to a **Binding** object.
 * @return BindingList* Pointer to a newly created **BindingList** object.
 */
BindingList* createBindingListFromBinding( Binding* b ) {

    BindingList* r = (BindingList*) malloc( sizeof(BindingList) );
    
    r->id = idGenerator++;
    r->prevBindings = NULL;
    r->binding = b;

    return r;

}

/**
 * @brief Constructor to append a new **Binding** to an existing **BindingList** object.
 * 
 * @param lst A pointer to an existing **BindingList** object.
 * @param b A pointer to a **Binding** object.
 * @return BindingList* Pointer to a newly created **BindingList** object.
 */
BindingList* appendBinding( BindingList* lst, Binding* b ) {

    BindingList* r = (BindingList*) malloc( sizeof(BindingList) );
    r->id = idGenerator++;
    r->prevBindings = lst;
    r->binding = b;
    
}

/**
 * @brief Destructor for a **BindingList** object.
 * 
 * @param BindingList A pointer to the **BindingList** object you want to destruct.
 */
void freeBindingList(BindingList* bindingList) {

    freeBinding( bindingList->binding );
    free( bindingList->binding );
    bindingList->binding = NULL;

    if( bindingList->prevBindings != NULL ) {
        freeBindingList( bindingList->prevBindings );
    }

    free( bindingList->prevBindings );
    bindingList->prevBindings = NULL;

}

/**
 * @brief Internal function to print a string representation of a **BindingList** object.
 * 
 * @param lst A pointer to the **BindingList** object you want to print.
 */
void printBindingListElements( BindingList* lst ) {

    printBinding( lst->binding );

    if( lst->prevBindings != NULL ) {
        printf("\n");
        printBindingListElements(lst->prevBindings);
    }

}

/**
 * @brief Prints a formatted string representation of a **BindingList** object.
 * 
 * @param lst A pointer to the **BindingList** object you want to print.
 */
void printBindingList( BindingList* lst ) {

    printf( "\n----------------------------------------\n\n" );

    printf("Binding List:\n");
    printf("-------------\n");
    
    printf("\n");

    printBindingListElements( lst );

    printf("\n");
    printf("\nEND\n");

    printf( "\n----------------------------------------\n\n" );

    

}

/**
 * @brief Internal function to build a graphiz representation of the dependencies of a **BindingList**. (Used by **buildBindingListNode**)
 * 
 * @param lst A pointer to an **BindingList** object.
 * @param fp A valid file pointer.
 * @param id The id of the "top level" **BindingList**. 
 */
void buildBindingListArrows( BindingList* lst, FILE* fp, unsigned int id ) {

    fprintf( fp, "%u -> %u;\n", id, lst->binding->id );
    buildBindingNode( lst->binding, fp );

    if( lst->prevBindings != NULL ) {
        buildBindingListArrows( lst->prevBindings, fp, id );
    }

}

/**
 * @brief Builds a graphviz representation of a **BindingList** object and prints it to a file.
 * 
 * @param lst A pointer to an **BindingList** object.
 * @param fp A valid file pointer.
 */
void buildBindingListNode( BindingList* lst, FILE* fp ) {

    fprintf( fp, "%u [label=\"%s\"];\n", lst->id, "Binding List" );
    buildBindingListArrows( lst, fp, lst->id );

}