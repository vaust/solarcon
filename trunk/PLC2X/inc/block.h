/*
 * block.h
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "gen_types.h"

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

typedef struct block_par_s {
    int a;
    int b;
    int c;
} block_par_t;

typedef struct block_st_s {
    int u[16];
    int y[16];
} block_st_t;

typedef std_ret_t (*block_read_u_t)(block_in_t *);
typedef std_ret_t (*block_write_y_t)(block_out_t *);

typedef struct block_class_s {
    /** @brief state describing data of the block */
    block_st_t       st;
    /** @brief parameters describing the block    */
    block_par_t      par;
    /** @brief Input interface                    */
    block_read_u_t   read_u;
    /** @brief Output interface                   */
    block_write_y_t  write_y;
    /** @brief block methodes                     */
    std_ret_t (*Open) (struct block_class_s *self);
    std_ret_t (*Run)  (struct block_class_s *self);
    std_ret_t (*Close)(struct block_class_s *self);
} block_class_t;

std_ret_t block_Init( block_class_t*  self,
                      block_read_u_t  read_f,
                      block_write_y_t write_f );

/*
std_ret_t block_Open(block_class_t *self);
std_ret_t block_Run(block_class_t *self);
std_ret_t block_Close(block_class_t *self);
*/
#endif /* BLOCK_H_ */
