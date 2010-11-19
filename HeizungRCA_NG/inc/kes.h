#ifndef _KES_H_
#define _KES_H_

#include "gen_types.h"

/* <Typen> */
typedef struct {
    float sp_dt_sw;                 /**< Globaler Wert div 2 !! */
    float ww_tww_sw;
} kes_param_t;

typedef struct {
    float        sp1_to_mw;
    float        sp2_to_mw;
    float        tvl_mw;
    u32_t        gz_mw;         /**< Gaszaehlerstand (noch nicht in Verwendung */
    float        hk_tvl_sw;     
    float        fb_tvl_sw;
    nutzzeit_t   duschzeit;
    di_bitbyte_t br_bm;
} kes_in_t;

typedef struct {
    float sp1_to_sw;
    float sp2_to_sw;
    float tvl_sw_sp1;           /**< Kesselvorlaufsollwert fuer Speicher 1 nur zur Info und Debugging */
    float tvl_sw_sp2;           /**< Kesselvorlaufsollwert fuer Speicher 1 nur zur Info und Debugging */
    float tvl_sw;               /**< eigentlicher Kesselvorlaufsollwert (Maximum aus tvl_sw_sp1 und tvl_sw_sp2 */
    do_bitbyte_t pu_sp1_sb;     /**< Pumpen Relais Speicher Pumpe 1 */
    do_bitbyte_t pu_sp2_sb;     /**< Pumpen Relais Speicher Pumpe 2 */
} kes_out_t;
/* <Typen/> */

/* <Prototypen> */
void kes_Init( kes_param_t *par_p, kes_out_t *out_p );
void kes_Run( const kes_param_t *par_p, 
              const kes_in_t    *in_p,
                    kes_out_t   *out_p );
void kes_WriteInp(       kes_in_t     *in_p,
		           const float         sp1_to_mw,
		           const float         sp2_to_mw,
		           const float         tvl_mw,
		           const u32_t         gz_mw,
		           const float         hk_tvl_sw,
		           const float         fb_tvl_sw,
		           const nutzzeit_t    duschzeit,
		           const di_bitbyte_t  br_bm      );
/* <Prototypen/> */

#endif /* _KES_H_ */

