

#ifndef BNF
    
    #define BNF

    #include <stdlib.h>
    
    struct Terminal {

        unsigned int id;
        char* regex;

    }; typedef struct Terminal Terminal;

    Terminal* createTerminal( char* Regex );
    void freeTerminal(Terminal* term);
    void printTerminal( Terminal* term );
    void buildTerminalNode( Terminal* term, FILE* fp );

    struct NonTerminal {

        unsigned int id;
        char* Name;

    }; typedef struct NonTerminal NonTerminal;

    NonTerminal* createNonTerminal( char* Name );
    void freeNonTerminal( NonTerminal* nterm );
    void printNonTerminal( NonTerminal* nterm );
    void buildNonTerminalNode( NonTerminal* nterm, FILE* fp );


    enum SymbolType {

        TERM,
        NONTERM

    };

    struct Symbol {

        unsigned int id;
        enum SymbolType type;
        union {
            NonTerminal* nterm;
            Terminal* term;
        };

    }; typedef struct Symbol Symbol;

    Symbol* createNonTerminalSymbol( NonTerminal* nterm );
    Symbol* createTerminalSymbol( Terminal* term );
    void freeSymbol( Symbol* symbol );
    void printSymbol( Symbol* symbol );
    void buildSymbolNode( Symbol* symbol, FILE* fp );


    struct AndExpr {

        unsigned int id;
        AndExpr* prevAndExpr;
        Symbol* symbol;

    }; typedef struct AndExpr AndExpr;

    AndExpr* createAndExpr( Symbol* symbol );
    AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol );
    void freeAndExpr(AndExpr* AndExpression);
    void printAndExpr( AndExpr* AndExpression );
    void buildAndExprNode( AndExpr* AndExpression, FILE* fp );


    struct OrExpr {

        unsigned int id;
        OrExpr* prevOrExpr;
        AndExpr* AndExpression;

    }; typedef struct OrExpr OrExpr;

    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );
    void freeOrExpr( OrExpr* OrExpression );
    void printOrExpr( OrExpr* OrExpression );
    void buildOrExprNode( OrExpr* OrExpression, FILE* fp );


    struct Binding {

        unsigned int id;
        NonTerminal* nterm;
        OrExpr* OrExpression; 

    }; typedef struct Binding Binding;
    
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );
    void freeBinding( Binding* binding );
    void printBinding( Binding* b );
    void buildBindingNode( Binding* b, FILE* fp );


    struct BindingList {

        unsigned int id;
        BindingList* prevBindings;
        Binding* binding;

    }; typedef struct BindingList BindingList;

    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding* b );
    void freeBindingList( BindingList* bindingList );
    void printBindingList( BindingList* lst );
    void buildBindingListNode( BindingList* lst, FILE* fp );

    extern unsigned int idGenerator;

#endif
