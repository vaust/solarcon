#include <stdio.h>
#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );

void cntrl_FB_Heizkreis( void )
{
    float           xd;                        /* Regelabweichung               */
    static float    xd_alt = 0.0;              /* vorhergehende Regelabweichung */

    float           fb_prim_mv_y_f;            /* Stellwert in Fliesskomma      */
    static float    fb_prim_mv_y_alt_f = 50.0; /* vorhergehender Stellwert      */
    float           q0, q1;      /* Parameter für den digitalen PI Algorithmus  */
    const float     TA = 1.0;    /* Abtastzeit in sec                           */

    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    fb_Tvl_SW_f = toGradCelsius(fb_tr_sw - ALL_Tau_MW) * fb_tvl_steigung +
                  toGradCelsius(fb_tr_sw) + fb_tvl_niveau;
    if( (z_FB_Zustand == zAbgesenkt) && (partytime_flg == RESET) ) {
        fb_Tvl_SW_f -= toGradCelsius(fb_tvl_absenk);
    }
    if( fb_Tvl_SW_f < toGradCelsius(fb_tvl_min) ) {
        fb_Tvl_SW_f = toGradCelsius(fb_tvl_min);
    }
    else if( fb_Tvl_SW_f > toGradCelsius(fb_tvl_max) ) {
        fb_Tvl_SW_f = toGradCelsius(fb_tvl_max);
    }

    /* Mischventil Regleralgorithmus ansteuern */
    xd = fb_Tvl_SW_f - toGradCelsius(FB_SEK_Tvl_MW);
    /* Berechnung von q0 und q1:*/
    q0 =  fb_reg_kp + TA/(60.0*fb_reg_tn);
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

#ifdef __DEBUG__
    printf( "DEBUG: Fussbodenheizung Vorlauftemperatur Sollwert  = %5.2f\n", fb_Tvl_SW_f );
    printf( "DEBUG: Fussbodenheizung Vorlauftemperatur Istwert   = %5.2f\n", toGradCelsius(FB_SEK_Tvl_MW) );
    printf( "DEBUG: Regelabweichung der Vorlauftemperatur        = %5.2f\n", xd );
    printf( "DEBUG: Stellgroesse (float)                         = %5.2f\n", fb_prim_mv_y_f );
#endif

    if( ( (Tau_36h_mittel_f <  toGradCelsius(all_at_start)) || /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (ALL_Tau_MW       <  all_frostschutz            ) || /* Die Aussentemperatur liegt unter der Frostschutzmarke          */
          (partytime_flg    == SET)
        ) /* && (fb_prim_mv_y_f > 5.0) */ ) {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
#ifdef __DEBUG__
        printf( "DEBUG: Fussbodenheizung Pumpen EIN.\n" );
#endif
    }
    else if( ( (Tau_36h_mittel_f > (toGradCelsius(all_at_start)+1.0)) ||
               (FB_SEK_TW == IO_EIN)
              ) /* && (fb_prim_mv_y_f < 1.0) */ ) {
        FB_PRIM_PU_SB = IO_AUS;
        FB_SEK_PU_SB  = IO_AUS;
#ifdef __DEBUG__
        printf( "DEBUG: Fussbodenheizung Pumpen AUS.\n" );
#endif
    }
    else {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
#ifdef __DEBUG__
        printf( "DEBUG: Fussbodenheizung Pumpen EIN.\n" );
#endif
    }
}
