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
typedef struct sol_param_s {
    float sp_t_max;     /**< Maximal zulaessige Speichertemperatur                                      */
    float dt_ein_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil oeffnet   */
    float dt_aus_sw;    /**< Temperaturdifferenz zwischen Kollektor- und Speicher, die Ventil schliesst */
} sol_param_t;

typedef struct sol_sp_t_mw_s {
    float to_mw;        /**< Obere Speichertemperatur  */
    float tu_mw;        /**< Untere Speichertemperatur */
} sol_sp_t_mw_t;

typedef struct sol_in_s {
    float           koll_t_mw[SOL_N_KO];    /**< Array von Kollektortemperaturen (aktuell nur ein Element) */
    sol_sp_t_mw_t   t_sp[SOL_N_SP];         /**< Array auf Speichertemperaturpaare (aktuell 2 Elemente)    */
} sol_in_t;

typedef struct sol_out_s {
    do_bitbyte_t    av_sb[SOL_N_SP];        /**< Array auf Absperrventilzustaende  (aktuell 2 Elemente)       */
    do_bitbyte_t    pu_sb[SOL_N_KO];        /**< Array auf Kollektorpumpenzustaende (aktuell nur ein Element) */
} sol_out_t;   

typedef struct sol_class_s {
    sol_param_t p;
    sol_in_t    i;
    sol_out_t   o;
} sol_class_t;

/* <Typen/> */
/* <Prototypen> */

void sol_Init( sol_class_t *self );
s16_t sol_Run(  sol_class_t *self );

void sol_WriteInp(       sol_class_t *self,
                   const float        koll_t_mw,
                   const float        sp1_to_mw,
                   const float        sp1_tu_mw,
                   const float        sp2_to_mw,
                   const float        sp2_tu_mw );
/* <Prototypen/> */

#endif /* _SOL_H_ */

