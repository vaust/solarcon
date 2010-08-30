#ifdef __IO_MASTER__
#error "__IO_MASTER_ in falschem File definiert!"
#else
#define __IO_MASTER__
#endif 

#include "solar.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "io.h"

int main( void )
{
    sol_in_t sol_in_Sp1, sol_in_Sp2;
    int sol_sp1_av_sb, sol_sp2_av_sb, sol_pu_sb;
    sol_param_t sol_par;
    
    sol_par.sp_t_max = 120.0;
    sol_par.dt_ein_sw = 2.0;
    sol_par.dt_aus_sw = 2.0;
    
    solar_Init( &sol_par );
    
    sol_in_Sp1.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp1.sp_to_mw = SOL_SP1_To_MW;
    sol_in_Sp1.sp_tu_mw = SOL_SP1_Tu_MW;
        
    sol_in_Sp2.koll_t_mw = ALL_Tau_MW;
    sol_in_Sp2.sp_to_mw = SOL_SP2_To_MW;
    sol_in_Sp2.sp_tu_mw = SOL_SP2_Tu_MW;
      
    solar_Run(  &sol_par, 
                &sol_in_Sp1,    &sol_in_Sp2, 
                &sol_sp1_av_sb, &sol_sp2_av_sb,
                &sol_pu_sb );

    return( 0 );
}
