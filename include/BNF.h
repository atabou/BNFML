

#ifndef BNF
    
    #define BNF
    
    typedef struct Terminal Terminal;
    Terminal* createTerminal( char* Regex );
    void freeTerminal(Terminal* term);

    typedef struct NonTerminal NonTerminal;
    NonTerminal* createNonTerminal( char* Name );
    void freeNonTerminal(NonTerminal* term);

    typedef struct Symbol Symbol;
    Symbol* createNonTerminalSymbol( NonTerminal* nterm );
    Symbol* createTerminalSymbol( Terminal* term );
    void freeSymbol(Symbol* symbol);

    typedef struct AndExpr AndExpr;
    AndExpr* createAndExpr( Symbol* symbol );
    AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol );
    void freeAndExpr(AndExpr* AndExpression);

    typedef struct OrExpr OrExpr;
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );
    void freeOrExpr(OrExpr* OrExpression);

    typedef struct Binding Binding;
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );
    void freeBinding(Binding* binding);

    typedef struct BindingList BindingList;
    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding* b );
    void freeBindingList(BindingList* bindingList);

    extern unsigned int idGenerator;

#endif
