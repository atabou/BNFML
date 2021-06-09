
/**
 * 
 * @file ExecutionGraph.c
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Implementation file for the functions related to the **ExecutionGraph** struct.
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ExecutionGraph.h"
#include "ParserTree.h"


ExecutionGraph* createExecutionGraph( ExecutionNode* node, ExecutionGraph* DirectParent );
int appendNewBranch( ExecutionGraph* tree, ExecutionGraph* branch );

ExecutionGraph* exploreOrExpr( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst );
ExecutionGraph* exploreOrExpr_Recursive( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst );

ExecutionGraph* exploreAndExpr( AndExpr* a, ExecutionGraph* DirectParent, BindingList* lst );
ExecutionGraph* exploreAndExpr_Recursive( AndExpr* a, ExecutionGraph* DirectParent, BindingList* lst );

ExecutionGraph* exploreNonTerminal( BindingList* lst,  NonTerminal* nterm, ExecutionGraph* DirectParent );
ExecutionGraph* verfifyRecursiveness( ExecutionGraph* tree, char* nterm );

ExecutionGraph* exploreTerminal( Terminal* term, ExecutionGraph* DirectParent );

typedef struct ExecutionGraphNodeList ExecutionGraphNodeList;
ExecutionGraph* ExecutionGraphBFS( ExecutionGraph* tree, ExecutionGraph** lst, int* n );

/**************************************************************************************************
 *                                                                                                *
 *                                        DEFINITIONS                                             *
 *                                                                                                *
 **************************************************************************************************/

/**
 * @struct **ExecutionGraph**
 * @brief struct to define an **ExecutionGraph** used when processing a parsed **BindingList**
 * 
 */
struct ExecutionGraph {

    ExecutionNode* Node; /**< A pointer to the node this object represents. */
    
    int NumberOfBranches; /** An integer representing the number of branches for this node */
    ExecutionGraph** Branches; /**< A pointer to a list of the next execution branches. */

    ExecutionGraph* DirectParent; /**< A pointer to the parent node of this object. It is only used internally to deal with recursiveness, do not use. */
    int visited; /**< An integer representing if a node has been visited. Used internally to deal with memory management, do not use */

};

/**
 * @brief Constructor to create an **ExecutionGraph**.
 * 
 * @param lst A pointer to a **BindingList** Object.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* buildExecutionGraph( BindingList* lst ) {

    Binding* unique = verifyUniquenessOfBindings( lst );

    if( unique != NULL ) {

        printf( "\n[Error] Non-Terminal: %s, has two assignments.\n", unique->nterm->Name );
        exit(-1);
    
    } else {
    
        printf( "\n[SUCCESS] All Non-Terminals are unique.\n" );
    
    }

    Binding* start = searchForBinding( lst, "<bnf>" );

    if( start == NULL ) {
    
        printf( "[ERROR] Starting Non-Terminal value: <bnf> not found.\n" );
        exit(-1);
    
    } else {
    
        printf( "%s\n", start->nterm->Name );
        printf( "[SUCCESS] Starting Non-Terminal <bnf> found.\n" );
    
    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( start->nterm );

    printf( "[SUCCESS] Initialised <bnf> Non-Terminal node.\n" );

    ExecutionGraph* tree = createExecutionGraph( NonTerminalNode, NULL );

    printf( "[SUCCESS] Successfully initialised the execution graph.\n" );

    ExecutionGraph* OrTree = exploreOrExpr( start->OrExpression, tree, lst );

    printf( "[SUCCESS] Finished exploring the bindings.\n" );

    appendNewBranch( tree, OrTree );

    printf( "[SUCCESS] Successfully finished building the execution tree.\n" );

    return tree;

}

void buildGraphvizExecutionGraphRepresentation( ExecutionGraph* G, FILE* fp ) {

    G->visited = 1;

    buildGraphvizExecutionNodeRepresentation( G->Node, fp );

    for( int i=0; i < G->NumberOfBranches; i++ ) {

        fprintf( fp, "%u -> %u;\n", G->Node->id, G->Branches[i]->Node->id );

        if( G->Branches[i]->visited == 0 ) {
            buildGraphvizExecutionGraphRepresentation( G->Branches[i], fp );
        }

    }

}

/**
 * @brief Destructor for an **ExecutionGraph** object.
 * 
 * @param tree A pointer to the **ExecutionGraph** object you want to destruct.
 */
void freeExecutionGraph_Implementation(ExecutionGraph* G, int visited_value) {

    if( G->visited == visited_value ) {

        return ;

    } else {

        freeExecutionNode( G->Node );
        free(G->Node);
        G->Node = NULL;

        G->visited = 1;

        for( int i=0; i < G->NumberOfBranches; i++ ) {

            if( G->Branches[i]->visited == visited_value ) {

                freeExecutionGraph_Implementation( G->Branches[i], visited_value );
                free( G->Branches[i] );
                G->Branches[i] = NULL;

            }

        }

        free( G->Branches );
        G->Branches = NULL;
        
    }

}


/**
 * @brief Destructor for an **ExecutionGraph** object.
 * 
 * @param tree A pointer to the **ExecutionGraph** object you want to destruct.
 */
void freeExecutionGraph(ExecutionGraph* G) {

    freeExecutionGraph_Implementation( G, G->visited );

}




/**************************************************************************************************
 *                                                                                                *
 *                                          HELPERS                                               *
 *                                                                                                *
 **************************************************************************************************/

/**
 * @brief Create an **ExecutionGraph** object. (Internal Function)
 * 
 * @param node A pointer to an **ExecutionNode** object.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* createExecutionGraph( ExecutionNode* node, ExecutionGraph* DirectParent ) {

    ExecutionGraph* tree = (ExecutionGraph*) malloc( sizeof(ExecutionGraph) );

    tree->Node = node;

    tree->NumberOfBranches = 0;
    tree->Branches = NULL;

    tree->DirectParent = DirectParent;

    return tree;

}

/**
 * @brief Append a new branch to an existing **ExecutionGraph**. (Internal Function)
 * 
 * @param tree A pointer to an existing **ExecutionGraph**.
 * @param branch A pointer to an existing **ExecutionGraph**
 * 
 * @return int An integer representing if the append operation was successful
 */
int appendNewBranch( ExecutionGraph* tree, ExecutionGraph* branch ) {

    if( branch == NULL || tree == NULL ) {
        return 0;
    }

    int n = tree->NumberOfBranches;

    ExecutionGraph** branches = (ExecutionGraph**) malloc ( sizeof( ExecutionGraph* ) * (n+1) );

    branches[0] = branch;

    for( int i=0; i<n; i++ ) {
        branches[i+1] = tree->Branches[i];
    }

    ExecutionGraph** tmp = tree->Branches;
    free(tmp);

    tree->NumberOfBranches = n+1;
    tree->Branches = branches;
    
    return 1;
    
}

/**
 * @brief Creates an **ExecutionGraph** representing a **OrExpr** object.
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreOrExpr( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst  ) {

    printf( "Exploring OrTree: %u\n", OrExpression->id );

    if( OrExpression->prevOrExpr != NULL ) {

        printOrExpr( OrExpression );

        ExecutionGraph* OrTree = exploreOrExpr_Recursive( OrExpression->prevOrExpr, DirectParent, lst );
        
        ExecutionGraph* AndTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        appendNewBranch( OrTree, AndTree );

        return OrTree;
        
    } else {

        ExecutionGraph* OrTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        return OrTree;

    }

    printf( "Finished OrTree: %u\n", OrExpression->id );

}

/**
 * @brief Creates an **ExecutionGraph** representing a **OrExpr** object. (Helper method for **exploreOrExpr**)
 * 
 * @param OrExpression A pointer to an **OrExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreOrExpr_Recursive( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst ) {

    printf( "Exploring Rec OrTree: %u\n", OrExpression->id );

    if( OrExpression == NULL ) {

        ExecutionNode* OrNode = createOrExecutionNode( );
        ExecutionGraph* OrTree = createExecutionGraph( OrNode, DirectParent );

        return OrTree;

    } else {

        ExecutionGraph* OrTree =  exploreOrExpr_Recursive( OrExpression->prevOrExpr, DirectParent, lst );        
        
        ExecutionGraph* AndTree = exploreAndExpr( OrExpression->AndExpression, OrTree, lst );
        appendNewBranch( OrTree, AndTree );

        return OrTree;

    }

    printf( "Finished Rec OrTree: %u\n", OrExpression->id );

}

/**
 * @brief Creates an **ExecutionGraph** representing an **AndExpr** object.
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreAndExpr( AndExpr* AndExpression, ExecutionGraph* DirectParent, BindingList* lst ) {

    printf( "Exploring AndTree: %u\n", AndExpression->id );

    if( AndExpression->prevAndExpr != NULL ) {

        ExecutionGraph* AndTree = exploreAndExpr_Recursive( AndExpression->prevAndExpr, DirectParent, lst );

        if( AndExpression->type == TERM ) {
            
            ExecutionGraph* TerminalTree = exploreTerminal( AndExpression->term, AndTree );
            appendNewBranch( AndTree, TerminalTree );

        } else {

            ExecutionGraph* NonTerminalTree = exploreNonTerminal(lst, AndExpression->nterm, AndTree);
            appendNewBranch( AndTree, NonTerminalTree );

        }
        
        return AndTree;

    } else {

        ExecutionGraph* AndTree;

        if( AndExpression->type == TERM ) {
        
            AndTree = exploreTerminal( AndExpression->term, DirectParent );
        
        } else {
        
            AndTree = exploreNonTerminal( lst, AndExpression->nterm, DirectParent );
        
        }

        return AndTree;

    }

    printf( "Finished AndTree: %u\n", AndExpression->id );

}

/**
 * @brief Creates an **ExecutionGraph** representing a **AndExpr** object. (Helper method for **exploreAndExpr**)
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @param lst A pointer to the **BindingList** being processed.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreAndExpr_Recursive( AndExpr* AndExpression, ExecutionGraph* DirectParent, BindingList* lst ) {

    printf( "Exploring AndTree: %u\n", AndExpression->id );

    if( AndExpression == NULL ) {

        ExecutionNode* AndNode = createAndExecutionNode( );
        ExecutionGraph* AndTree = createExecutionGraph( AndNode, DirectParent );

        return AndTree;

    } else {

        ExecutionGraph* AndTree = exploreAndExpr_Recursive( AndExpression->prevAndExpr, DirectParent, lst );

        if( AndExpression->type == TERM ) {
            
            ExecutionGraph* TerminalTree = exploreTerminal( AndExpression->term, AndTree );
            appendNewBranch( AndTree, TerminalTree );

        } else {

            ExecutionGraph* NonTerminalTree = exploreNonTerminal(lst, AndExpression->nterm, AndTree);
            appendNewBranch( AndTree, NonTerminalTree );

        }
        
        return AndTree;

    }

    printf( "Finished AndTree: %u\n", AndExpression->id );

}

/**
 * @brief Creates an **ExecutionGraph** representing a **NonTerminal** object.
 * 
 * @param lst A pointer to the **BindingList** being processed.
 * @param nterm A pointer to a **NonTerminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreNonTerminal( BindingList* lst, NonTerminal* nterm, ExecutionGraph* DirectParent ) {

    Binding* b = searchForBinding( lst, nterm->Name );

    if( b == NULL ) {
        printf( "NonTerminal: %s is not defined as a binding.", nterm->Name );
        exit( -1 );
    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( nterm );
    ExecutionGraph* NonTerminalTree = createExecutionGraph( NonTerminalNode, DirectParent );

    ExecutionGraph* RecursiveNode = verfifyRecursiveness(DirectParent, nterm->Name);

    if( RecursiveNode == NULL ) {

        ExecutionGraph* OrTree = exploreOrExpr( b->OrExpression, NonTerminalTree, lst );
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
 * @param tree A pointer to the **ExecutionGraph** for which its **ExecutionNode** should be checked.
 * @param nterm A string representing the value to be checked.
 * @return ExecutionGraph* A pointer to the **ExecutionGraph** that was found to have a value of **nterm**. (If not found, returns NULL)
 */
ExecutionGraph* verfifyRecursiveness( ExecutionGraph* tree, char* nterm ) {

    if( tree == NULL ) {

        return NULL;

    } else if( tree->Node->NodeType == NON_TERMINAL_NODE && strcmp(tree->Node->nterm, nterm) == 0 ) {

        return tree;

    } else {

        verfifyRecursiveness( tree->DirectParent, nterm );

    }


}

/**
 * @brief Creates an **ExecutionGraph** representing a **Terminal** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
ExecutionGraph* exploreTerminal( Terminal* term, ExecutionGraph* DirectParent ) {

    ExecutionNode* TerminalNode = createTerminalExecutionNode( term );
    ExecutionGraph* TerminalTree = createExecutionGraph( TerminalNode, DirectParent );

    return TerminalTree;

}
 

