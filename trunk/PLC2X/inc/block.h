/*
 * block.h
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#ifndef BLOCK_H_
#define BLOCK_H_

typedef struct block_in_s {
    int a;
    int b;
    int c;
} block_in_t;

typedef struct block_out_s {
    int d;
    int e;
    int f;
} block_out_t;

typedef std_return_t (block_read_u_t *)(block_in_t *);
typedef std_return_t (block_write_y_t*)(block_out_t *);

typedef struct block_class_s {
    int history[16];
    int para_a;
    int para_b;
    int para_c;
    block_read_u_t read_u;
    block_write_y_t write_y;
    std_return_t (*Run)( struct block_class_s *self);
} block_class_t;

std_return_t block_Init( block_class_t*  self,
                           block_read_u_t  read_f,
                           block_write_y_t write_f );

std_return_t block_Run(block_class_t *self);

#endif /* BLOCK_H_ */
