#define _SOLAR_C_

#include "solar.h"

void solar_Init( sol_param_t *par_p )
{
    /* nichts zu initialisieren */
}

static int solar_Speicherabsperrventil( const sol_param_t *par_p, const sol_in_t *in_p, int *sp_av_sb_p )
{
    int errorcode;
    
    if( in_p->sp_to_mw < par_p->sp_t_max ) {
        /* Die Kollektortemperatur liegt unter dem Maximalwert  */
        if( in_p->koll_t_mw > ( in_p->sp_tu_mw + par_p->dt_ein_sw ) ) {
            *sp_av_sb_p  = IO_AUF;
        }
        else {
            if( in_p->koll_t_mw <= ( in_p->sp_tu_mw + par_p->dt_aus_sw ) ) {
                *sp_av_sb_p  = IO_ZU;
            }
            else {
                *sp_av_sb_p  = IO_AUF;
            }
        }
        errorcode = SOLAR_NORMAL;
    } 
    else {
        /* Die Kollektortemperatur liegt ueber dem Maximalwert  */
        *sp_av_sb_p  = IO_ZU;
        errorcode = SOLAR_UEBERTEMPERATUR;
    }
    return( errorcode );
}

static void solar_Pumpe( const sol_param_t *par_p, const int *sp1_av_sb_p, const int *sp2_av_sb_p, int *sol_pu_sb_p )
{
    if( ( *sp1_av_sb_p == IO_ZU ) && 
        ( *sp2_av_sb_p == IO_ZU )    ) {
        *sol_pu_sb_p = IO_AUS;
    } 
    else {
        *sol_pu_sb_p = IO_EIN;
    }
}    
        
int solar_Run(  const sol_param_t *par_p,
                const sol_in_t    *in_Sp1_p, 
                const sol_in_t    *in_Sp2_p, 
                      int         *sp1_av_sb_p, 
                      int         *sp2_av_sb_p,
                      int         *sol_pu_sb_p )
{
    int errorcode;
    
    errorcode = solar_Speicherabsperrventil( par_p, in_Sp1_p, sp1_av_sb_p ); /* Absperrventil Speicher 1 */
    errorcode = solar_Speicherabsperrventil( par_p, in_Sp2_p, sp2_av_sb_p ); /* Absperrventil Speicher 2 */
    solar_Pumpe( par_p, sp1_av_sb_p, sp2_av_sb_p, sol_pu_sb_p );
    return( errorcode );
}

