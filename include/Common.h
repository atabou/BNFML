
#ifndef COMMON_H
#define COMMON_H

    typedef struct CommonInterface {

        unsigned int (*getID)( void* this );
        void (*print)( void* this );
        void (*build_Graphviz)( void* this, FILE* fp );
        void (*destruct)( void* this );

    } CommonInterface;

    extern unsigned int ParserID_Generator;
    extern unsigned int ExecutionID_Generator;

#endif