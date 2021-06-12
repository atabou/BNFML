
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

void exploreOrExpr( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst );
void exploreAndExpr( AndExpr* a, ExecutionGraph* DirectParent, BindingList* lst );
void exploreNonTerminal( NonTerminal* nterm, ExecutionGraph* DirectParent, BindingList* lst );
void exploreTerminal( Terminal* term, ExecutionGraph* DirectParent );

ExecutionGraph* verfifyRecursiveness( ExecutionGraph* tree, char* nterm );

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

    Binding* unique = lst->allElementsUnique( lst );

    if( unique != NULL ) {

        NonTerminal* nterm = unique->getNonTerminal(unique);
        printf( "\n[Error] Non-Terminal: %s, has two assignments.\n", nterm->getName(nterm) );
        exit(-1);
    
    } else {
    
        printf( "\n[SUCCESS] All Non-Terminals are unique.\n" );
    
    }

    Binding* start = lst->search( lst, "<bnf>" );

    if( start == NULL ) {
    
        printf( "[ERROR] Starting Non-Terminal value: <bnf> not found.\n" );
        exit(-1);
    
    } else {
    
        NonTerminal* nterm = start->getNonTerminal( start );
        printf( "%s\n", nterm->getName(nterm) );
        printf( "[SUCCESS] Starting Non-Terminal <bnf> found.\n" );
    
    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( start->getNonTerminal(start) );
    ExecutionGraph* G = createExecutionGraph( NonTerminalNode, NULL );
    exploreOrExpr( start->getOrExpr(start), G, lst );

    printf( "[SUCCESS] Finished exploring the bindings.\n" );
    printf( "[SUCCESS] Successfully finished building the execution tree.\n" );

    return G;

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
    tree->visited = 0;

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
void exploreOrExpr( OrExpr* OrExpression, ExecutionGraph* DirectParent, BindingList* lst  ) {

    AndExpr** branches = OrExpression->getBranches( OrExpression );

    if ( OrExpression->length(OrExpression) == 1 ) {

        printf( "Starting exploration of AND expression, id: %d\n", branches[0]->getID( branches[0] ) );
        exploreAndExpr( branches[0], DirectParent, lst );
        printf( "[SUCCESS] Finished exploration of AND expression, id: %d\n", branches[0]->getID( branches[0] ) );

    } else {

        ExecutionNode* OrNode = createOrExecutionNode( );
        ExecutionGraph* OrGraph = createExecutionGraph( OrNode, DirectParent );

        for( int i=0; i<OrExpression->length(OrExpression); i++ ) {

            printf( "Starting exploration of AND expression, id: %d\n", branches[i]->getID( branches[i] ) );
            exploreAndExpr( branches[i], OrGraph, lst );
            printf( "[SUCCESS] Finished exploration of AND expression, id: %d\n", branches[i]->getID( branches[i] ) );

        }

        appendNewBranch( DirectParent, OrGraph );

    }

}

/**
 * @brief Creates an **ExecutionGraph** representing an **AndExpr** object.
 * 
 * @param AndExpression A pointer to an **AndExpr** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @param lst A pointer to the **BindingList** being processed.
 */
void exploreAndExpr( AndExpr* expr, ExecutionGraph* DirectParent, BindingList* lst ) {

    int n = expr->length( expr );

    if( n == 1 ) {

        if( expr->branches[0]->getDynamicType(  ) == TERMINAL_SYMBOL ) {

            Terminal* term = (Terminal*) expr->branches[0];

            printf( "Starting exploration of Terminal: %s, id: %d\n", term->getValue(term), term->getID(term) );
            exploreTerminal( term, DirectParent );
            printf( "[SUCCESS] Finished exploration of Terminal: %s, id: %d\n", term->getValue(term), term->getID(term) );

        } else if( expr->branches[0]->getDynamicType(  ) == NON_TERMINAL_SYMBOL ) {

            NonTerminal* nterm = (NonTerminal*) expr->branches[0];

            printf( "Starting exploration of Non-Terminal: %s, id: %d\n", nterm->getName(nterm), nterm->getID( nterm ) );
            exploreNonTerminal( nterm, DirectParent, lst );
            printf( "[SUCCESS] Finished exploration of Non-Terminal: %s, id: %d\n", nterm->getName(nterm), nterm->getID(nterm) );

        }

    } else {

        ExecutionNode* AndNode = createAndExecutionNode( );
        ExecutionGraph* AndGraph = createExecutionGraph( AndNode, DirectParent );

        for( int i=0; i < n; i++ ) {


            if( expr->branches[i]->getDynamicType(  ) == TERMINAL_SYMBOL ) {

                Terminal* term = (Terminal*) expr->branches[i];

                printf( "Starting exploration of Terminal: %s, id: %d\n", term->getValue(term), term->getID(term) );
                exploreTerminal( term, AndGraph );
                printf( "[SUCCESS] Finished exploration of Terminal: %s, id: %d\n", term->getValue(term), term->getID(term) );

            } else if ( expr->branches[i]->getDynamicType(  ) == NON_TERMINAL_SYMBOL ) {

                NonTerminal* nterm = (NonTerminal*) expr->branches[i];
                
                printf( "Starting exploration of Non-Terminal: %s, id: %d\n", nterm->getName(nterm), nterm->getID( nterm ) );
                exploreNonTerminal( nterm, AndGraph, lst );
                printf( "[SUCCESS] Finished exploration of Non-Terminal: %s, id: %d\n", nterm->getName(nterm), nterm->getID( nterm ) );

            }

        }

        appendNewBranch( DirectParent, AndGraph );

    }

}


/**
 * @brief Creates an **ExecutionGraph** representing a **NonTerminal** object.
 * 
 * @param lst A pointer to the **BindingList** being processed.
 * @param nterm A pointer to a **NonTerminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
void exploreNonTerminal( NonTerminal* nterm, ExecutionGraph* DirectParent, BindingList* lst ) {

    Binding* b = lst->search( lst, nterm->getName(nterm) );

    if( b == NULL ) {

        printf( "NonTerminal: %s is not defined as a binding.\n", nterm->getName(nterm) );
        exit( -1 );

    }

    ExecutionNode* NonTerminalNode = createNonTerminalExecutionNode( nterm );
    ExecutionGraph* NonTerminalGraph = createExecutionGraph( NonTerminalNode, DirectParent );

    ExecutionGraph* RecursiveNode = verfifyRecursiveness( DirectParent, nterm->getName(nterm) );

    if( RecursiveNode == NULL ) {

        OrExpr* expr = b->getOrExpr(b);

        printf( "Starting exploration of OR exprssion, id: %d\n", expr->getID(expr)  );
        exploreOrExpr( expr, NonTerminalGraph, lst );
        printf( "Starting exploration of OR exprssion, id: %d\n", expr->getID(expr) );

    } else {

        NonTerminal* rec = b->getNonTerminal(b);

        printf( "Found a recursive call at Non-Terminal: %s, from id: %d to id: %d\n", nterm->getName(nterm), nterm->getID(nterm), rec->getID( rec ) );
        appendNewBranch( NonTerminalGraph, RecursiveNode );
        printf( "[SUCCESS] Added a recursive call for Non-Terminal: %s, from id: %d to id: %d\n", nterm->getName(nterm), nterm->getID( nterm ), rec->getID( rec ) );

    }

    appendNewBranch( DirectParent, NonTerminalGraph );

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
ExecutionGraph* verfifyRecursiveness( ExecutionGraph* G, char* nterm ) {

    if( G == NULL ) {

        return NULL;

    } else if( G->Node->NodeType == NON_TERMINAL_NODE && strcmp(G->Node->nterm, nterm) == 0 ) {

        return G;

    } else {

        verfifyRecursiveness( G->DirectParent, nterm );

    }


}

/**
 * @brief Creates an **ExecutionGraph** representing a **Terminal** object.
 * 
 * @param term A pointer to a **Terminal** object.
 * @param DirectParent A pointer to the direct parent of the object to be created in the **ExecutionGraph**.
 * @return ExecutionGraph* A pointer to a newly created **ExecutionGraph** object.
 */
void exploreTerminal( Terminal* term, ExecutionGraph* DirectParent ) {

    
    ExecutionNode* TerminalNode = createTerminalExecutionNode( term );
    ExecutionGraph* TerminalGraph = createExecutionGraph( TerminalNode, DirectParent );

    appendNewBranch( DirectParent, TerminalGraph );

}
 

