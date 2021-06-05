
#ifndef OREXPR

    #define OREXPR

    #include "BNF.h"

    typedef struct OrExpr OrExpr;
    OrExpr* createOrExpr( AndExpr* AndExpression );
    OrExpr* appendAndExpr( OrExpr* lst, AndExpr AndExpression );


#endif