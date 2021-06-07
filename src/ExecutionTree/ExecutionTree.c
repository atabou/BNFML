
/**
 * 
 * @file ExecutionTree.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Implementation file for the functions related to the **ExecutionTree** struct.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ExecutionTree.h"
#include "ParserTree.h"


ExecutionTree* createExecutionTree( ExecutionNode* node, ExecutionTree* DirectParent );
int appendNewBranch( ExecutionTree* tree, ExecutionTree* branch );

ExecutionTree* exploreOrExpr( OrExpr* OrExpression, ExecutionTree* DirectParent, BindingList* lst );
ExecutionTree* exploreOrExprRec( OrExpr* OrExpression, ExecutionTree* DirectParent, BindingList* lst );

ExecutionTree* exploreAndExpr( AndExpr* a, ExecutionTree* DirectParent, BindingList* lst );
ExecutionTree* exploreAndExprRec( AndExpr* a, ExecutionTree* DirectParent, BindingList* lst );

ExecutionTree* exploreNonTerminal( BindingList* lst,  NonTerminal* nterm, ExecutionTree* DirectParent );
ExecutionTree* verfifyRecursiveness( ExecutionTree* tree, char* nterm );

ExecutionTree* exploreTerminal( Terminal* term, ExecutionTree* DirectParent );


/**
 * @struct **ExecutionTree**
 * @brief struct to define an **ExecutionTree** used when processing a parsed **BindingList**
 * 
 */
struct ExecutionTree {

    ExecutionNode* node; /**< A pointer to the node this object represents. */
    
    int NumberOfBranches;
    ExecutionTree** branches; /**< A pointer to a list of the next execution branches. */

    ExecutionTree* DirectParent; /**< A pointer to the parent node of this object. It is only used internally to deal with recursiveness, do not use. */

};

/**
 * @brief Constructor to create an **ExecutionTree**.
 * 
 * @param lst A pointer to a **BindingList** Object.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* buildExecutionTree( BindingList* lst ) {

    Binding* unique = verifyUniquenessOfBindings( lst );

    if( !unique ) {
        printf( "Error: Non-Terminal: %s, has two assignments.", unique->nterm->Name );
        exit(-1);
    }

    Binding* start = searchForBinding( lst, "bnf" );

    if( start == NULL ) {
        printf( "Error: Starting Non-Terminal value: <bnf> not found." );
        exit(-1);
    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( start->nterm );
    ExecutionTree* tree = createExecutionTree( NonTerminalNode, NULL );

    ExecutionTree* OrTree = exploreOrExpr( start->OrExpression, tree, lst );
    appendNewBranch( tree, OrTree );

    return tree;

}

/**
 * @brief Destructor for an **ExecutionTree** object.
 * 
 * @param tree A pointer to the **ExecutionTree** object you want to destruct.
 */
void freeExecutionTree(ExecutionTree* tree) {

}



/**************************************************************************************************
 *                                                                                                *
 *                                          HELPERS                                               *
 *                                                                                                *
 **************************************************************************************************/

/**
 * @brief Create an **ExecutionTree** object. (Internal Function)
 * 
 * @param node A pointer to an **ExecutionNode** object.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* createExecutionTree( ExecutionNode* node, ExecutionTree* DirectParent ) {

    ExecutionTree* tree = (ExecutionTree*) malloc( sizeof(ExecutionTree) );

    tree->node = node;

    tree->NumberOfBranches = 0;
    tree->branches = NULL;

    tree->DirectParent = DirectParent;

    return tree;

}

/**
 * @brief Append a new branch to an existing **ExecutionTree**
 * 
 * @param tree A pointer to an existing **ExecutionTree**.
 * @param branch A pointer to an existing **ExecutionTree**
 * 
 * @return int An integer representing if the append operation was successful
 */
int appendNewBranch( ExecutionTree* tree, ExecutionTree* branch ) {

    if( branch == NULL || tree == NULL ) {
        return 0;
    }

    int n = tree->NumberOfBranches;

    ExecutionTree** branches = (ExecutionTree**) malloc ( sizeof( ExecutionTree* ) * (n+1) );

    branches[0] = branch;

    for( int i=0; i<n; i++ ) {
        branches[i+1] = tree->branches[i];
    }

    ExecutionTree** tmp = tree->branches;
    free(tmp);

    tree->NumberOfBranches = n+1;
    tree->branches = branches;
    
    return 1;
    
}

/**
 * @brief Creates an **ExecutionTree** representing a **OrExpr** object.
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreOrExpr( OrExpr* OrExpression, ExecutionTree* DirectParent, BindingList* lst  ) {

    if( OrExpression->prevOrExpr != NULL ) {

        ExecutionTree* OrTree = exploreOrExprRec( OrExpression->prevOrExpr, DirectParent, lst );
        
        ExecutionTree* AndTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        appendNewBranch( OrTree, AndTree );

        return OrTree;
        
    } else {

        ExecutionTree* OrTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        return OrTree;

    }

    

}

/**
 * @brief Creates an **ExecutionTree** representing a **OrExpr** object. (Helper method for **exploreOrExpr**)
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreOrExprRec( OrExpr* OrExpression, ExecutionTree* DirectParent, BindingList* lst ) {

    if( OrExpression == NULL ) {

        ExecutionNode* OrNode = createOrExecutionNode( );
        ExecutionTree* OrTree = createExecutionTree( OrNode, DirectParent );

        return OrTree;

    } else {

        ExecutionTree* OrTree =  exploreOrExprRec( OrExpression->prevOrExpr, DirectParent, lst );        
        
        ExecutionTree* AndTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        appendNewBranch( OrTree, AndTree );

        return OrTree;

    }

}

/**
 * @brief Creates an **ExecutionTree** representing a **AndExpr** object.
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreAndExpr( AndExpr* AndExpression, ExecutionTree* DirectParent, BindingList* lst ) {

    if( AndExpression->prevAndExpr != NULL ) {

        ExecutionTree* AndTree = exploreAndExprRec( AndExpression->prevAndExpr, DirectParent, lst );

        if( AndExpression->type == TERM ) {
            
            ExecutionTree* TerminalTree = exploreTerminal( AndExpression->term, AndTree );
            appendNewBranch( AndTree, TerminalTree );

        } else {

            ExecutionTree* NonTerminalTree = exploreNonTerminal(lst, AndExpression->nterm, AndTree);
            appendNewBranch( AndTree, NonTerminalTree );

        }
        
        return AndTree;

    } else {

        ExecutionTree* AndTree;

        if( AndExpression->type == TERM ) {
        
            AndTree = exploreTerminal( AndExpression->term, DirectParent );
        
        } else {
        
            AndTree = exploreNonTerminal( lst, AndExpression->nterm, DirectParent );
        
        }

        return AndTree;

    }

}

/**
 * @brief Creates an **ExecutionTree** representing a **AndExpr** object. (Helper method for **exploreAndExpr**)
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreAndExprRec( AndExpr* AndExpression, ExecutionTree* DirectParent, BindingList* lst ) {

    if( AndExpression == NULL ) {

        ExecutionNode* AndNode = createAndExecutionNode( );
        ExecutionTree* AndTree = createExecutionTree( AndNode, DirectParent );

        return AndTree;

    } else {

        ExecutionTree* AndTree = exploreAndExprRec( AndExpression->prevAndExpr, DirectParent, lst );

        if( AndExpression->type == TERM ) {
            
            ExecutionTree* TerminalTree = exploreTerminal( AndExpression->term, AndTree );
            appendNewBranch( AndTree, TerminalTree );

        } else {

            ExecutionTree* NonTerminalTree = exploreNonTerminal(lst, AndExpression->nterm, AndTree);
            appendNewBranch( AndTree, NonTerminalTree );

        }
        
        return AndTree;

    }

}

/**
 * @brief Creates an **ExecutionTree** representing a **NonTerminal** object.
 * 
 * @param lst A pointer to the **BindingList** being processed.
 * @param nterm A pointer to a **NonTerminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreNonTerminal( BindingList* lst, NonTerminal* nterm, ExecutionTree* DirectParent ) {

    Binding* b = searchForBinding( lst, nterm->Name );

    if( b == NULL ) {
        printf( "NonTerminal: %s is not defined as a binding.", nterm->Name );
        exit( -1 );
    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( nterm );
    ExecutionTree* NonTerminalTree = createExecutionTree( NonTerminalNode, DirectParent );

    ExecutionTree* RecursiveNode = verfifyRecursiveness(DirectParent, nterm->Name);

    if( RecursiveNode == NULL ) {

        ExecutionTree* OrTree = exploreOrExpr( b->OrExpression, NonTerminalTree, lst );
        appendNewBranch( NonTerminalTree, OrTree );

    } else {

        appendNewBranch( NonTerminalTree, RecursiveNode );

    }

    return NonTerminalTree;

}

/**
 * @brief Verifies if any NonTerminal node in the parent stack of some NonTerminal node has a value of **nterm**.
 * 
 * Used to verify if a recursive definition of a **NonTerminal** object exists in the tree.
 * 
 * @param tree A pointer to the **ExecutionTree** for which its **ExecutionNode** should be checked.
 * @param nterm A string representing the value to be checked.
 * @return ExecutionTree* A pointer to the **ExecutionTree** that was found to have a value of **nterm**. (If not found, returns NULL)
 */
ExecutionTree* verfifyRecursiveness( ExecutionTree* tree, char* nterm ) {

    if( tree == NULL ) {

        return NULL;

    } else if( tree->node->NodeType == NON_TERMINAL_NODE && strcmp(tree->node->nterm, nterm) ) {

        return tree;

    } else {

        verfifyRecursiveness( tree->DirectParent, nterm );

    }


}

/**
 * @brief Creates an **ExecutionTree** representing a **Terminal** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionTree**.
 * @return ExecutionTree* A pointer to a newly created **ExecutionTree** object.
 */
ExecutionTree* exploreTerminal( Terminal* term, ExecutionTree* DirectParent ) {

    ExecutionNode* TerminalNode = createTerminalExecutionNode( term );
    ExecutionTree* TerminalTree = createExecutionTree( TerminalNode, DirectParent );

    return TerminalTree;

}
    

