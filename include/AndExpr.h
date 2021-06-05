
#ifndef ADDEXPR

    #define ADDEXPR

    #include "BNF.h"

    typedef struct AndExpr AndExpr;
    AndExpr* createAndExpr( Symbol* Expression );
    AndExpr* appendExpression( AndExpr* lst, Symbol* Expression );


#endif