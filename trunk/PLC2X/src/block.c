/*
 * block.c
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#include "gen_types.h"
#include "block.h"

std_ret_t block_Init( block_class_t*  self,
                      block_read_u_t  read_f,
                      block_write_y_t write_f )
{
    int i;

    self->read_u = read_f;
    self->write_y = write_f;
    self->Run = block_Run;
    self->para_a = 2;
    self->para_b = 5;

    for( i=0; i<16; i++ ) {
        self->history[i] = 0;
    }
    return E_OK;
}

std_ret_t block_Run(block_class_t *self)
{
    block_in_t  u;
    block_out_t y;

    if( self->read_u(&u) == E_OK ) {
        y.f = (self->para_a*u.a + self->para_b)*u.b;
        if(self->write_y(&y) != E_OK) {
            // irgendetwas ist faul
        }
    }
    else {
        // irgendetwas ist faul
    }

    return E_OK;
}
