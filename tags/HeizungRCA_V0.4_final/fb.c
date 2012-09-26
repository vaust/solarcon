#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );

void cntrl_FB_Heizkreis( void )
{
    float           xd;                        /* Regelabweichung               */
    static float    xd_alt = 0.0;              /* vorhergehende Regelabweichung */

    float           fb_prim_mv_y_f;            /* Stellwert in Fliesskomma      */
    static float    fb_prim_mv_y_alt_f = 50.0; /* vorhergehender Stellwert      */
    float           q0, q1;                    /* Parameter für den digitalen PI Algorithmus  */
    const float     TA = 1.0;                  /* Abtastzeit in sec                           */

    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    fb_Tvl_SW_f = (fb_tr_sw - ALL_Tau_MW) * fb_tvl_steigung + fb_tr_sw + fb_tvl_niveau;
    if( (z_FB_Zustand == zAbgesenkt) && (partytime_flg == RESET) ) {
        fb_Tvl_SW_f -= fb_tvl_absenk;
    }
    if( fb_Tvl_SW_f < fb_tvl_min ) {
        fb_Tvl_SW_f = fb_tvl_min;
    }
    else if( fb_Tvl_SW_f > fb_tvl_max ) {
        fb_Tvl_SW_f = fb_tvl_max;
    }

    /* Mischventil Regleralgorithmus ansteuern */
    xd = fb_Tvl_SW_f - FB_SEK_Tvl_MW;
    /* Berechnung von q0 und q1:*/
    q0 =  fb_reg_kp + TA/fb_reg_tn;
    q1 = -fb_reg_kp;
    fb_prim_mv_y_f = fb_prim_mv_y_alt_f + q0*xd + q1*xd_alt ;
    fb_prim_mv_y_alt_f = fb_prim_mv_y_f;
    xd_alt = xd;

    /* Mischventil mit 0-10V ansteuern */
    if( fb_prim_mv_y_f <= MIN_Y_PCT ) {
        fb_prim_mv_y_f = MIN_Y_PCT;
        fb_prim_mv_y_alt_f = MIN_Y_PCT;
    }
    else if( fb_prim_mv_y_f >= MAX_Y_PCT ) {
        fb_prim_mv_y_f = MAX_Y_PCT;
        fb_prim_mv_y_alt_f = MAX_Y_PCT;
    }

    ProzentToAnalogOut( fb_prim_mv_y_f , (ao_0_10V_t*) &FB_PRIM_MV_Y );

    if(   (Tau_36h_mittel_f <  all_at_start ) && /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (fb_Tvl_SW_f      >  20.0         )
        ) {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
    }
    else if( Tau_36h_mittel_f > (all_at_start+1.0) ) {
        FB_PRIM_PU_SB = IO_AUS;
        FB_SEK_PU_SB  = IO_AUS;
    }
    else if( ALL_Tau_MW <  all_frostschutz ) {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
    }
}
