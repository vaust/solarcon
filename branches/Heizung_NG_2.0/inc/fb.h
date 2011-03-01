#ifndef _FB_H_
#define _FB_H_

#include "gen_types.h"
#include "reg.h"

/* <Typen> */
typedef struct fb_param_s {
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float frostschutz;
    float tr_sw;
} fb_param_t;

typedef struct fb_in_s {
    float       tau_mw;
    float       tau_avg;
    float       sek_tvl_mw;
    abgesenkt_t zustand;
    u8_t        partytime_flg;
} fb_in_t;

typedef struct fb_out_s {
    float            tvl_sw;
    float            prim_mv_y;
    do_bitbyte_t     prim_pu_sb;
    do_bitbyte_t     sek_pu_sb;
} fb_out_t;
/* <Typen/> */

typedef struct fb_class_s {
    reg_class_t reg;
    fb_param_t  p;
    fb_in_t     i;
    fb_out_t    o;
} fb_class_t;

/* <Prototypen> */
void fb_Init( fb_class_t *self );
void fb_Run( fb_class_t *self );
void fb_WriteInp(       fb_class_t   *self,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        sek_tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg );
/* <Prototypen/> */

#endif /* _FB_H_ */

