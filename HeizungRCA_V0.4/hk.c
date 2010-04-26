#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );

/* Regler fuer den Waermetauscher, der den Heizkoerperheizkreis beheizt */
void cntrl_HK_Heizkreis( void )
{
    float           xd;             /* Regelabweichung      */
    static float    xd_alt = 0.0;
    static float    hk_mv_y_alt_f = 50.0;
    float           q0, q1;
    const float     TA = 1.0;       /* Abtastzeit in sec    */

    /* Vorlauftemperatursollwert im Floatformat berechnen   */
    hk_Tvl_SW_f = (hk_tr_sw - ALL_Tau_MW) * hk_tvl_steigung + hk_tr_sw + hk_tvl_niveau;
    if( (z_HK_Zustand == zAbgesenkt) && (partytime_flg == RESET) ) {
        hk_Tvl_SW_f -= hk_tvl_absenk;
    }
    if( hk_Tvl_SW_f < hk_tvl_min ) {
        hk_Tvl_SW_f = hk_tvl_min;
    }
    else if( hk_Tvl_SW_f > hk_tvl_max ) {
        hk_Tvl_SW_f = hk_tvl_max;
    }

    /* Regelabweichung Soll - Ist */
    xd = hk_Tvl_SW_f - HK_Tvl_MW;
    /* Mischventil ueber PI-Regler ansteuern */
    q0 =  hk_reg_kp + TA/hk_reg_tn;
    q1 = -hk_reg_kp;
    hk_mv_y_f = hk_mv_y_alt_f + q0*xd + q1*xd_alt ;
    hk_mv_y_alt_f = hk_mv_y_f;
    xd_alt = xd;

    if( hk_mv_y_f >= MAX_Y_PCT ) {
        hk_mv_y_f = MAX_Y_PCT;
        hk_mv_y_alt_f = MAX_Y_PCT;
    }
    else if( hk_mv_y_f <= MIN_Y_PCT ) {
        hk_mv_y_f = MIN_Y_PCT;
        hk_mv_y_alt_f = MIN_Y_PCT;
    }

    /* Mischventil mit 0-10V ansteuern */
    ProzentToAnalogOut( hk_mv_y_f , (ao_0_10V_t*) &HK_MV_Y );

    if( ( (Tau_36h_mittel_f <  all_at_start    ) ||
          /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (ALL_Tau_MW       <  all_frostschutz ) ||
          /* Die Aussentemperatur liegt unter der Frostschutzmarke          */
          (partytime_flg    == SET             )
        ) && (hk_mv_y_f > 5.0) ) {
        HK_PU_SB = IO_EIN; /* Heizkreis Pumpe einschalten */
    }
    else if( Tau_36h_mittel_f > (all_at_start+1.0) ) {
        HK_PU_SB = IO_AUS;     /* Heizkreis Pumpe ausschalten */
    }
    else {
        HK_PU_SB = IO_EIN; /* Heizkreis Pumpe einschalten */
    }
}
