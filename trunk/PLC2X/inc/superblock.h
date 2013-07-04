/*
 * superblock.h
 *
 *  Created on: 26.09.2012
 *      Author: stegmv
 */

#ifndef SUPERBLOCK_H_
#define SUPERBLOCK_H_

#include "gen_types.h"
#include "block.h"

typedef struct superblock_in_s {
    int a;
    int b;
    int c;
} superblock_in_t;

typedef struct superblock_out_s {
    int d;
    int e;
    int f;
} superblock_out_t;

typedef struct superblock_par_s {
    int a;
    int b;
    int c;
} superblock_par_t;

typedef struct superblock_st_s {
    int u[16];
    int y[16];
} superblock_st_t;

typedef std_ret_t (*superblock_read_u_t)(superblock_in_t *);
typedef std_ret_t (*superblock_write_y_t)(superblock_out_t *);

typedef struct superblock_class_s {
    /** @brief state describing data of the superblock  */
    superblock_st_t       st;
    /** @brief parameters describing the superblock     */
    superblock_par_t      par;
    /** @brief Input interface                          */
    superblock_read_u_t   read_u;
    /** @brief Output interface                         */
    superblock_write_y_t  write_y;

    /** @brief two internal instances of a block        */
    block_class_t         subblock1;
    block_class_t         subblock2;

    /** @brief superblock methodes                      */
    std_ret_t (*Open) (struct superblock_class_s *self);
    std_ret_t (*Run)  (struct superblock_class_s *self);
    std_ret_t (*Close)(struct superblock_class_s *self);
} superblock_class_t;

std_ret_t superblock_Init( superblock_class_t*  self,
                      superblock_read_u_t  read_f,
                      superblock_write_y_t write_f );

/*
std_ret_t superblock_Open(superblock_class_t *self);
std_ret_t superblock_Run(superblock_class_t *self);
std_ret_t superblock_Close(superblock_class_t *self);
*/
#endif /* BLOCK_H_ */
