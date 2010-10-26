#ifndef _SOL_H_
#define _SOL_H_

#include "gen_types.h"

/* <Defines> */
#define SOL_NORMAL           0
#define SOL_UEBERTEMPERATUR -1

#define SOL_N_SP    2
#define SOL_N_KO    1

#define SP1     0
#define SP2     1
#define KO1     0
/* <Defines/> */

/* <Typen> */
typedef struct {
    float sp_t_max;     /**< Maximal zulässige Speichertemperatur                                       */
    float dt_ein_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil öffnet    */
    float dt_aus_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil schliesst */
}   sol_param_t;

typedef struct {
    float to_mw;        /**< Obere Speichertemperatur  */
    float tu_mw;        /**< Untere Speichertemperatur */
} sol_sp_t_mw_t;

typedef struct {
    float           koll_t_mw[SOL_N_KO];
    sol_sp_t_mw_t   t_sp[SOL_N_SP];
} sol_in_t;
/* <Typen/> */

typedef struct {
    do_bitbyte_t    av_sb[SOL_N_SP];
    do_bitbyte_t    pu_sb[SOL_N_KO];
} sol_out_t;   

/* <Prototypen> */
void sol_Init( sol_param_t *par_p );
s16_t sol_Run(  const sol_param_t  *par_p,
                const sol_in_t     *in_p,
                      sol_out_t    *out_p );
/* <Prototypen/> */


#endif /* _SOL_H_ */

