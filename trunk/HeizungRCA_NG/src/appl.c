#define __IO_MASTER__

#include <stdio.h>

#include "gen_types.h"
#include "param.h"
#include "zeit.h"
#include "task.h"
#include "solar.h"
#include "fb.h"
// #include "hk.h"
// #include "ww.h"
#include "io.h"

int main( void )
{
    int n;

    /* Variablen fuer Zeit */
    zeit_Betriebszustand_t zeit_absenkung;
    zeit_event_t           zeit_event;
    zeit_party_t zeit_party;

    task_tau_t   tau;

    /* Variablen fuer Solarkollektorsteuerung */
    sol_in_t     sol_in_Sp1, sol_in_Sp2;
    do_bitbyte_t sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb;
    sol_param_t  sol_par;

    fb_param_t   fb_par;
    fb_out_t     fb_out;
    fb_in_t      fb_in;
    sup_digreg_coeff_t fb_q;

    zeit_Init( &zeit_absenkung, &zeit_event );
    zeit_TEST_Schaltzeiten();

    task_Init( &tau, ALL_Tau_MW );

    param_Init();
    for( n=0; n<PARSE_SET_N; n++ ) {
        printf( Vorgaben[n].VarName );
        printf( "= " );
        printf( Vorgaben[n].format, *(float *)Vorgaben[n].VarPointer );
        printf( "\n" );
    }

    sol_par.sp_t_max = param_sol_sp_t_max;
    sol_par.dt_ein_sw = param_sol_dt_ein_sw;
    sol_par.dt_aus_sw = param_sol_dt_aus_sw;
    solar_Init( &sol_par );

    fb_par.frostschutz  = param_all_frostschutz;
    fb_par.at_start     = param_all_at_start;
    fb_par.reg_kp       = param_fb_reg_kp;
    fb_par.reg_tn       = param_fb_reg_tn;
    fb_par.TA           = 1.0;
    fb_par.tvl_absenk   = param_fb_tvl_absenk;
    fb_par.tvl_max      = param_fb_tvl_max;
    fb_par.tvl_min      = param_fb_tvl_min;
    fb_par.tvl_niveau   = param_fb_tvl_niveau;
    fb_par.tvl_steigung = param_fb_tvl_steigung;

    fb_Init( &fb_par, &fb_q, &fb_out );
/*
    sol_in_Sp1.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp1.sp_to_mw = SOL_SP1_To_MW;
    sol_in_Sp1.sp_tu_mw = SOL_SP1_Tu_MW;

    sol_in_Sp2.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp2.sp_to_mw = SOL_SP2_To_MW;
    sol_in_Sp2.sp_tu_mw = SOL_SP2_Tu_MW;
*/
    sol_in_Sp1.koll_t_mw = 85.0;
    sol_in_Sp1.sp_to_mw = 38.0;
    sol_in_Sp1.sp_tu_mw = 34.0;

    sol_in_Sp2.koll_t_mw = 85.0;
    sol_in_Sp2.sp_to_mw = 57.0;
    sol_in_Sp2.sp_tu_mw = 44.0;

    task_Run( ALL_PARTY, WW_PARTY, ALL_Tau_MW, &tau, &zeit_event, &zeit_party );
    zeit_Run( &zeit_absenkung, &zeit_schedule );
    solar_Run( &sol_par, &sol_in_Sp1, &sol_in_Sp2, &sol_sp1_av_sb, &sol_sp2_av_sb, &sol_pu_sb );
    fb_Run( &fb_par, &fb_q, &fb_in, &fb_out );

    printf( "Zeit: Absenkung Fußbodenheizung: %d\n", zeit_absenkung.FB_Zustand );
    printf( "sp1_av_sb=%d\nsp2_av_sb=%d\nsol_pu_sb=%d\n",
            sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb );


    return( 0 );
}
