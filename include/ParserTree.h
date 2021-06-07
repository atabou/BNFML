
/**
 * 
 * @file ParserTree.h
 * @author Andre Tabourian
 * @version 0.0.1
 * @date 6 Jun 2021
 * @brief Header file containing struct and function definition to create the objects that BNFML will be parsed into.
 * @bug No known bugs.
 */

#ifndef PARSER_TREE
    
    #define PARSER_TREE

    #include <stdlib.h>

    typedef struct Terminal Terminal;
    typedef struct NonTerminal NonTerminal;
    typedef struct AndExpr AndExpr;
    typedef struct OrExpr OrExpr;
    typedef struct Binding Binding;
    typedef struct BindingList BindingList;



    /**
     * \addtogroup Terminal
     * @{
     */

    /**
     * @struct **Terminal**
     * @brief struct to define a parsed **Terminal** value in BNFML
     * 
     */
    struct Terminal {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        char* regex; /**< A regular expression representing the values a terminal can take.*/

    }; 
    
    Terminal* createTerminal( char* Regex );
    
    void freeTerminal(Terminal* term);
    void printTerminal( Terminal* term );
    void buildTerminalNode( Terminal* term, FILE* fp );

    /** @} */



    /**
     * \addtogroup NonTerminal
     * @{
     */

    /**
     * @struct **NonTerminal**
     * @brief struct to define a parsed **NonTerminal** object in BNFML
     * 
     */
    struct NonTerminal {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        char* Name; /**< A string representing the name of a non-terminal.*/

    }; 

    
    NonTerminal* createNonTerminal( char* Name );

    void freeNonTerminal( NonTerminal* nterm );
    void printNonTerminal( NonTerminal* nterm );
    void buildNonTerminalNode( NonTerminal* nterm, FILE* fp );

    /** @} */



    /**
     * \addtogroup AndExpression
     * @{
     */


    /**
     * @enum SymbolType
     * @brief Enum to represent the types a symbol can be.
     * 
     */
    enum SymbolType {

        TERM, /**< Enum value to reprsent a **Terminal** value. */
        NONTERM /**< Enum value to represent a **NonTerminal** value. */

    };

    /**
     * @struct **AndExpr**
     * @brief struct to define a parsed **AndExpr** value in BNFML
     * 
     */
    struct AndExpr {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        AndExpr* prevAndExpr; /**< A pointer to an **AndExpr** object.*/
        enum SymbolType type; /**< Enum **SymbolType** used to determine the type of symbol this object contains */
        union {
            NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
            Terminal* term; /**< A pointer to a **Terminal** object.*/
        };

    }; 
    
    AndExpr* createTerminalAndExpr( Terminal* term );
    AndExpr* createNonTerminalAndExpr( NonTerminal* nterm );

    AndExpr* appendTerminal( AndExpr* lst, Terminal* term );
    AndExpr* appendNonTerminal( AndExpr* lst, NonTerminal* nterm );
    
    void freeAndExpr(AndExpr* AndExpression);
    void printAndExpr( AndExpr* AndExpression );
    void buildAndExprNode( AndExpr* AndExpression, FILE* fp );

    /** @} */

    /**
     * \addtogroup OrExpression
     * @{
     */

    /**
     * @struct **OrExpr**
     * @brief struct to define a parsed **OrExpr** value in BNFML
     * 
     */
    struct OrExpr {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        OrExpr* prevOrExpr; /**< A pointer to an **OrExpr** object.*/
        AndExpr* AndExpression; /**< A pointer to a **AndExpr** object.*/

    }; 
    
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );
    
    void freeOrExpr( OrExpr* OrExpression );
    void printOrExpr( OrExpr* OrExpression );
    void buildOrExprNode( OrExpr* OrExpression, FILE* fp );

    /** @} */



    /**
     * \addtogroup Binding
     * @{
     */

    /**
     * @struct **Binding**
     * @brief struct to define a parsed **Binding** value in BNFML
     * 
     */
    struct Binding {

        unsigned int id; /**< Global ID of the object. see: idGenerator*/
        NonTerminal* nterm; /**< A pointer to a **NonTerminal** object.*/
        OrExpr* OrExpression; /**< A pointer to a **OrExpr** object.*/

    }; 
    
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );
    
    void freeBinding( Binding* binding );
    void printBinding( Binding* b );
    void buildBindingNode( Binding* b, FILE* fp );

    /** @} */



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

    extern unsigned int idGenerator;

#endif
