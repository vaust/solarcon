#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );

void cntrl_WW_Heizkreis( void )
{
//  static int      old_ww_wz_mw = IO_AUS; /* Merker fuer vorhergehenden Status Wasserzaehlerimpuls */
//  static long     old_ww_Zaehler_l = 0;  /* Merker für vorhergehenden Wasserzaehlerstand */
    float           xd_pu;                    /* Regelabweichung Soll - Ist */
    static float    xd_pu_alt = 0;
//  float           ww_hzg_mv_y_f;
//  static float    ww_hzg_mv_y_alt_f = 50.0; /* % */
    float           ww_hzg_pu_y_f;
    static float    ww_hzg_pu_y_alt_f = 11.0; /* 11% ist Zirkulationsgrundwert */
    float           q0, q1;
    const float     TA = 1.0;    /* Abtastzeit in sec                           */

    /* Zirkulationspumpe ansteuern */
    if( (z_Zirk_Zustand == zEin) || (ALL_Tau_MW < all_frostschutz) ) {
        WW_ZIRK_PU_SB = IO_EIN;
        WW_HZG_PU_SB = IO_EIN;
    }
    else {
        WW_ZIRK_PU_SB = IO_AUS;
        WW_HZG_PU_SB = IO_AUS;
    }

    xd_pu = toGradCelsius(ww_tww_sw)-toGradCelsius(WW_Tww_MW);
    /* Berechnung von q0 und q1:*/
    q0 =  ww_hzg_reg_kp + TA/(60.0*ww_hzg_reg_tn);
    q1 = -ww_hzg_reg_kp;
    ww_hzg_pu_y_f = ww_hzg_pu_y_alt_f + q0*xd_pu + q1*xd_pu_alt;
    xd_pu_alt = xd_pu;
    ww_hzg_pu_y_alt_f = ww_hzg_pu_y_f;

    if( ww_hzg_pu_y_f <= 11.0 ) {
        ww_hzg_pu_y_f = 11.0;
        ww_hzg_pu_y_alt_f = 11.0;
    }
    else if( ww_hzg_pu_y_f >= 99.0 ) {
        ww_hzg_pu_y_f = MAX_Y_PCT;
        ww_hzg_pu_y_alt_f = MAX_Y_PCT;
    }

    ProzentToAnalogOut( ww_hzg_pu_y_f, (ao_0_10V_t *) &WW_HZG_PU_Y );


/* #define IO_VV_SP1       0x00
   #define IO_VV_SP2       0x01
*/
    /************************************************
     * Kriterium für Warmwasser Heizungsverteilventil
     ************************************************/
    if( WW_HZG_Trl_MW < 300 ) {
        WW_HZG_VV_SB = IO_VV_SP2;  // MAKRO muss stimmen! Was ist Richtung Sp1 ?? An oder Aus ?
    }
    else if( WW_HZG_Trl_MW >= (300+kes_sp_dt_sw) ) {
        WW_HZG_VV_SB = IO_VV_SP1;
    }

#ifdef __DEBUG__
    printf( "DEBUG: ww_hzg_reg_kp    = %5.1f \n", ww_hzg_reg_kp );
    printf( "DEBUG: ww_hzg_reg_tn    = %5.3f \n", ww_hzg_reg_tn );

    printf( "DEBUG: Warmwasser Pumpenstellwert     = %5.1f \n", ww_hzg_pu_y_f );
    printf( "DEBUG: Warmwasser Pumpenstellwert alt = %5.1f \n", ww_hzg_pu_y_alt_f );
    printf( "DEBUG: Warmwasser Temperatur          = %5.1f \n", toGradCelsius(WW_Tww_MW)  );
    printf( "DEBUG: Warmwasser Regelabw.r          = %5.1f \n", xd_pu );
    printf( "DEBUG: Warmwasser Vorlauftemperatur   = %5.1f \n", toGradCelsius(WW_HZG_Tvl_MW) );
#endif
}
