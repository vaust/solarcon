/*
 * block.c
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#include "gen_types.h"
#include "block.h"

/* PUBLIC */
std_ret_t superblock_Init( superblock_class_t*  self,
                           superblock_read_u_t  read_f,
                           superblock_write_y_t write_f,
                           block_read_u_t       subblock1_read_f,
                           block_write_y_t      subblock1_write_f,
                           block_read_u_t       subblock2_read_f,
                           block_write_y_t      subblock2_write_f )
{
    int i;

    self->read_u = read_f;
    self->write_y = write_f;
    self->Open  = superblock_Open;
    self->Run   = superblock_Run;
    self->Close = superblock_Close;

    block_Init( &(self->subblock1), subblock1_read_f, subblock1_write_f );
    block_Init( &(self->subblock2), subblock2_read_f, subblock2_write_f );

    return E_OK;
}

/* PRIVATE */
static
std_ret_t superblock_Open(superblock_class_t *self)
{
    // todo
    return E_OK;
}

/* PRIVATE */
static
std_ret_t superblock_Run(superblock_class_t *self)
{
    block_in_t  u;
    block_out_t y;

    if( self->read_u(&u) == E_OK ) {
        // y.f = (self->par.a * u.a + self->par.b) * u.b;
        // self->st.y[0] = y.f;
        
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
static
std_ret_t superblock_Close(superblock_class_t *self)
{
    // todo
    return E_OK;
}


