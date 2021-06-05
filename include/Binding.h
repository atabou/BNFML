
#ifndef BINDING

    #define BINDING

    #include "BNF.h"

    typedef struct Binding Binding;
    Binding* createBinding( NonTerminal* nterm, OrExpr* OrExpression );


#endif