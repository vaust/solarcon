#define _SOL_C_

#include "sol.h"
#include "param.h"

void sol_Init( sol_param_t *par_p )
{
    par_p->sp_t_max = param_sol_sp_t_max;
    par_p->dt_ein_sw = param_sol_dt_ein_sw;
    par_p->dt_aus_sw = param_sol_dt_aus_sw;
}

static int sol_Speicherabsperrventil( const sol_param_t   *par_p, 
                                      const float         koll_t_mw,
                                      const sol_sp_t_mw_t *t_sp_p,  
                                      do_bitbyte_t        *sp_av_sb_p )
{
    int errorcode;

    if( t_sp_p->to_mw < par_p->sp_t_max ) {
        /* Die Kollektortemperatur liegt unter dem Maximalwert  */
        if( koll_t_mw > ( t_sp_p->tu_mw + par_p->dt_ein_sw ) ) {
            *sp_av_sb_p  = IO_AUF;
        }
        else {
            if( koll_t_mw <= ( t_sp_p->tu_mw + par_p->dt_aus_sw ) ) {
                *sp_av_sb_p  = IO_ZU;
            }
            else {
                *sp_av_sb_p  = IO_AUF;
            }
        }
        errorcode = SOL_NORMAL;
    }
    else {
        /* Die Kollektortemperatur liegt ueber dem Maximalwert  */
        *sp_av_sb_p  = IO_ZU;
        errorcode = SOL_UEBERTEMPERATUR;
    }
    return( errorcode );
}

static void sol_Pumpe( const sol_param_t  *par_p,
                             sol_out_t    *out_p )
{
    if( ( out_p->av_sb[SP1] == IO_ZU ) &&
        ( out_p->av_sb[SP2] == IO_ZU )    ) {
        out_p->pu_sb[KO1] = IO_AUS;
    }
    else {
        out_p->pu_sb[KO1] = IO_EIN;
    }
}

int sol_Run(  const sol_param_t  *par_p,
              const sol_in_t     *in_p,
                    sol_out_t    *out_p )
{
    int errorcode = 0;
    
    /* Absperrventil Speicher 1 */
    errorcode  = sol_Speicherabsperrventil( par_p, in_p->koll_t_mw[KO1], &(in_p->t_sp[SP1]), &(out_p->av_sb[SP1]) ); 
    /* Absperrventil Speicher 2 */
    errorcode += sol_Speicherabsperrventil( par_p, in_p->koll_t_mw[KO1], &(in_p->t_sp[SP2]), &(out_p->av_sb[SP2]) ); 
    sol_Pumpe( par_p, out_p );
    return( errorcode );
}


