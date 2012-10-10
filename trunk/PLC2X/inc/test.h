#ifndef _TEST_H_
#define _TEST_H_

#include "gen_types.h"
#include "block.h"

/* Globals */
#undef PUBLIC
#ifdef _TEST_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

PUBLIC block_class_t Block1;

/* Prototypen */
void test_open( void );
void test_run( int sig );
void test_close( void );

#endif /* _TEST_H_ */

