/*
 * block.c
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#include "gen_types.h"
#include "block.h"

/* PUBLIC */
std_ret_t block_Init( block_class_t*  self,
                      block_read_u_t  read_f,
                      block_write_y_t write_f )
{
    int i;

    self->read_u = read_f;
    self->write_y = write_f;
    self->Open = block_Open;
    self->Run = block_Run;
    self->Close = block_Close;
    self->par.a = 2;
    self->par.b = 5;

    for( i=0; i<16; i++ ) {
        self->history[i] = 0;
    }
    return E_OK;
}

/* PRIVATE */
static
std_ret_t block_Open(block_class_t *self)
{
    // todo
    return E_OK;
}

/* PRIVATE */
static
std_ret_t block_Run(block_class_t *self)
{
    block_in_t  u;
    block_out_t y;

    if( self->read_u(&u) == E_OK ) {
        y.f = (self->par.a * u.a + self->par.b) * u.b;
        self->st.y[0] = y.f;
        if(self->write_y(&y) != E_OK) {
            // irgendetwas ist faul
        }
    }
    else {
        // irgendetwas ist faul
    }

    return E_OK;
}

/* PRIVATE */
std_ret_t block_Close(block_class_t *self)
{
    // todo
    return E_OK;
}


