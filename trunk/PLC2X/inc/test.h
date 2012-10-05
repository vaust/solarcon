#ifndef _TEST_H_
#define _TEST_H_

#include "gen_types.h"

/* Globals */
#undef PUBLIC
#ifdef _TEST_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif


/* Prototypen */
void test_open( void );
void test_run( int sig );
void test_close( void );

#endif /* _TEST_H_ */

