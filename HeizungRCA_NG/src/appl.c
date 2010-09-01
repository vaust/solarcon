#define __IO_MASTER__


#include <stdio.h>

#include "param.h"
#include "solar.h"
// #include "fb.h"
// #include "hk.h"
// #include "ww.h"
// #include "io.h"

int main( void )
{
    int n;
    
    sol_in_t sol_in_Sp1, sol_in_Sp2;
    int sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb;
    sol_param_t sol_par;
    
    param_Init();
    for( n=2; n<PARSE_SET_N; n++ ) {
        printf( Vorgaben[n].VarName );
        printf( "= " );
        printf( Vorgaben[n].format, *(float *)Vorgaben[n].VarPointer );
        printf( "\n" );
    }
    
    sol_par.sp_t_max = param_sol_sp_t_max;
    sol_par.dt_ein_sw = param_sol_dt_ein_sw;
    sol_par.dt_aus_sw = param_sol_dt_aus_sw;
    
    solar_Init( &sol_par );
/*    
    sol_in_Sp1.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp1.sp_to_mw = SOL_SP1_To_MW;
    sol_in_Sp1.sp_tu_mw = SOL_SP1_Tu_MW;
        
    sol_in_Sp2.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp2.sp_to_mw = SOL_SP2_To_MW;
    sol_in_Sp2.sp_tu_mw = SOL_SP2_Tu_MW;
*/
    sol_in_Sp1.koll_t_mw = 85.0;
    sol_in_Sp1.sp_to_mw = 38;
    sol_in_Sp1.sp_tu_mw = 34;
        
    sol_in_Sp2.koll_t_mw = 85.0;
    sol_in_Sp2.sp_to_mw = 57.0;
    sol_in_Sp2.sp_tu_mw = 44.0;
    
    solar_Run(  &sol_par, 
                &sol_in_Sp1,    &sol_in_Sp2, 
                &sol_sp1_av_sb, &sol_sp2_av_sb,
                &sol_pu_sb );

    printf( "sp1_av_sb=%d\nsp2_av_sb=%d\nsol_pu_sb=%d\n",
            sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb );   
    return( 0 );
}
