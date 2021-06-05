
#ifndef BNF
    
    #define BNF
    
    typedef struct Terminal Terminal;
    Terminal* createTerminal( char* Regex );

    typedef struct NonTerminal NonTerminal;
    NonTerminal* createNonTerminal( char* Name );

    typedef struct Symbol Symbol;
    Symbol* createNonTerminalSymbol( NonTerminal* nterm );
    Symbol* createTerminalSymbol( Terminal* term );

    typedef struct AndExpr AndExpr;
    AndExpr* createAndExpr( Symbol* symbol );
    AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol );

    typedef struct OrExpr OrExpr;
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );

    typedef struct Binding Binding;
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );

    typedef struct BindingList BindingList;
    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding* b );

    extern unsigned int idGenerator;
    


#endif
