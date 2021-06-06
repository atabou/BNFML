

#ifndef BNF
    
    #define BNF
    
    typedef struct Terminal Terminal;
    Terminal* createTerminal( char* Regex );
    void freeTerminal(Terminal* term);
    void printTerminal( Terminal* term );

    typedef struct NonTerminal NonTerminal;
    NonTerminal* createNonTerminal( char* Name );
    void freeNonTerminal( NonTerminal* nterm );
    void printNonTerminal( NonTerminal* nterm );

    typedef struct Symbol Symbol;
    Symbol* createNonTerminalSymbol( NonTerminal* nterm );
    Symbol* createTerminalSymbol( Terminal* term );
    void freeSymbol( Symbol* symbol );
    void printSymbol( Symbol* symbol );

    typedef struct AndExpr AndExpr;
    AndExpr* createAndExpr( Symbol* symbol );
    AndExpr* appendSymbol( AndExpr* lst, Symbol* symbol );
    void freeAndExpr(AndExpr* AndExpression);
    void printAndExpr( AndExpr* AndExpression );

    typedef struct OrExpr OrExpr;
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr* AndExpression );
    void freeOrExpr( OrExpr* OrExpression );
    void printOrExpr( OrExpr* OrExpression );

    typedef struct Binding Binding;
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );
    void freeBinding( Binding* binding );
    void printBinding( Binding* b );

    typedef struct BindingList BindingList;
    BindingList* createBindingListFromBinding( Binding* b );
    BindingList* appendBinding( BindingList* lst, Binding* b );
    void freeBindingList( BindingList* bindingList );
    void printBindingList( BindingList* lst );

    extern unsigned int idGenerator;

#endif
