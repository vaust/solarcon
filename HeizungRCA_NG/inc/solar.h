#ifndef _SOLAR_H_
#define _SOLAR_H_

#include "gen_types.h"

/* <Defines> */
#define SOLAR_NORMAL           0
#define SOLAR_UEBERTEMPERATUR -1
/* <Defines/> */

/* <Typen> */
typedef struct {
    float sp_t_max;
    float dt_ein_sw;
    float dt_aus_sw;
}   sol_param_t;

typedef struct {
    float koll_t_mw;
    float sp_to_mw;
    float sp_tu_mw;
} sol_in_t;
/* <Typen/> */

/* <Prototypen> */
void solar_Init( sol_param_t *par_p );
int solar_Run(  const sol_param_t *par_p,
                const sol_in_t    *in_Sp1_p, 
                const sol_in_t    *in_Sp2_p, 
                      int         *sp1_av_sb_p, 
                      int         *sp2_av_sb_p,
                      int         *sol_pu_sb_p );
/* <Prototypen/> */

/* <lokale Protypen>  */
static int solar_Speicherabsperrventil( const sol_param_t *par_p, 
                                 const sol_in_t    *in_p, 
                                       int         *sp_av_sb_p );
static void solar_Pumpe( const sol_param_t *par_p,
                  const int *sp1_av_sb_p, 
                  const int *sp2_av_sb_p, 
                        int *sol_pu_sb_p );
/* <lokale Protypen/> */ 

#endif /* _SOLAR_H_ */
