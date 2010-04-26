/* Debugeinstellungen */
#define __DEBUG__ 1
#define __MAIN__
// #define __MODULTEST__
#define __WAGO__
#define TEST 2
// #define __LOGFILE__

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#endif

#include <string.h>
#include <time.h>

#include "io.h"
#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
float toGradCelsius( temp10_pt1000_t messstelle );
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang );
void cntrl_initAverageTau( temp10_pt1000_t currTau );
int cntrl_zeitprogramm( void );
void log_variables( FILE *fp );

/* Digitale Regler */
void cntrl_Solarbeheizung( void );
void cntrl_Speicher1( void );
void cntrl_Speicher2( void );
void cntrl_Kessel( void );
void cntrl_FB_Heizkreis( void );
void cntrl_HK_Heizkreis( void );
void cntrl_WW_Heizkreis( void );

void cntrl_task( void );
void cntrl_min_task( void );
void cntrl_hour_task( void );

/* externe Funktionsprototypen, die in diesem Modul verwendet werden  */
extern int init_parameters( void );
extern int init_zeitprogramm( void );
extern void init_variables( void );

/* Hilfsfunktionen         */
/* Temperaturrohwert in Grad C */
float toGradCelsius( temp10_pt1000_t messstelle )
{
    return( ((float) messstelle)/10.0 );
}

/* %-Wert in 0-10V Stellgroesse umrechnen */
void ProzentToAnalogOut( float scale ,ao_0_10V_t *ausgang )
{
	*ausgang = (ao_0_10V_t) ((scale*VFULLSCALE)/100);
}

void cntrl_task( void )
{
    static int  old_ALL_PARTY = IO_AUS;
    static int  old_WW_PARTY = IO_AUS;

#ifdef __WAGO__
 	KbusUpdate();
#endif
	cntrl_zeitprogramm();

    /* ALL_Party Flag ermitteln */
    if( ( ALL_PARTY >= IO_EIN ) && ( old_ALL_PARTY == IO_AUS ) ) {
        partytime_flg = SET;  /* Ruecksetzen in cntrl_min_task() */
        minutes_since_party_pressed = all_partydauer;
    }
    old_ALL_PARTY = ALL_PARTY;

//    /* WW_Party Flag ermitteln */
//    if( ( WW_PARTY >= IO_EIN ) && ( old_WW_PARTY == IO_AUS ) ) {
//        ww_partytime_flg = SET;  /* Ruecksetzen in cntrl_min_task() */
//        ww_minutes_since_party_pressed = all_partydauer;
//    }
//    old_ALL_PARTY = ALL_PARTY;

	if( schedule_min_flg == SET ) {
		cntrl_min_task();
		schedule_min_flg = RESET;
	}
	if( schedule_hour_flg == SET ) {
		cntrl_hour_task();
		schedule_hour_flg = RESET;
	}

//    cntrl_Solarbeheizung();
    cntrl_FB_Heizkreis();
    cntrl_HK_Heizkreis();
	cntrl_WW_Heizkreis();

    /* Ansteuerung der Speicher unbedingt nach FB und HK,
     * da abhaengig von berechneten Sollwerten
     */
    cntrl_Speicher1();
    cntrl_Speicher2();
    /* Kesselansteuerung ist abhaengig von Speicherbeschickung */
    cntrl_Kessel();

#ifdef __WAGO__
	KbusUpdate();
#endif
}

void cntrl_min_task( void )
{
	static int		index = 0;
	int             n;
    temp10_pt1000_t ta_neu;
	temp10_pt1000_t ta_tminus60min;

    FILE *fp;

    /* Partyflag Ruecksetzzeitpunkt ermitteln */
    if(  minutes_since_party_pressed > 0 ) {
        minutes_since_party_pressed --;
    }
    else {
        partytime_flg = RESET;
    }
    /* Partyflag auf jeden Fall zuruecksetzen, wenn Partyschalter wieder ausgeschaltet wird */
    if( ALL_PARTY == IO_AUS ) {
        partytime_flg = RESET;
    }

  	/* Berechnung des 1 Stundenmittelwerts der Aussentemperatur aus 60 Werten alle Minuten */
	ta_neu           = ALL_Tau_MW;
	ta_tminus60min   = Tau_1min_Intervall[index];
	Tau_1h_Summe_sl += ta_neu - ta_tminus60min;
	Tau_1min_Intervall[index] = ta_neu;
	index ++;
	if( index > 59 ) {
		index = 0;
	}
	Tau_1h_mittel_f = ((float) Tau_1h_Summe_sl)/600.0;

#ifdef __LOGFILE__
    /* Logfile Eintraege schreiben */
    fp = fopen( "RCA.log", "a" );
    if( fp != NULL ) {
		log_variables( fp );
		fclose( fp );
	}
#endif

#ifdef __DEBUG__
/*  for( n=0; n<60; n++ ) {
        printf( "Tau_1min_Intervall[%d] = %d\n", n, Tau_1min_Intervall[n] );
    }
*/
    printf( "Mittlere Aussentemperatur ueber eine Stunde: %5.2f, index = %d\n", Tau_1h_mittel_f, index );
    printf( "Partyzeit = %d; Partyrestzeit = %d\n",  partytime_flg, minutes_since_party_pressed );
#endif
}

void cntrl_hour_task( void )
{
	static int		index = 0;
    int             n;
	float			ta_1h_mittel_neu_f;
	float			ta_1h_mittel_tminus36h;

	/* Berechnung des 36h (default) Mittelwerts der Au�entemperatur aus 36 1h Mittelwerten */
	ta_1h_mittel_neu_f     = Tau_1h_mittel_f;
	ta_1h_mittel_tminus36h = Tau_1h_mittel_36h_Intervall[index];
	Tau_36h_Summe_f       += ta_1h_mittel_neu_f - ta_1h_mittel_tminus36h;
    index ++;
	if( index >= MAX_ALL_Tau_mittel_Zeit ) {
		index = 0;
	}
	Tau_36h_mittel_f = Tau_36h_Summe_f / MAX_ALL_Tau_mittel_Zeit;

#ifdef __DEBUG__
/*  for( n=0; n<MAX_ALL_Tau_mittel_Zeit; n++ ) {
        printf( "Tau_1min_Intervall[%d] = %d\n", n, Tau_1h_mittel_36h_Intervall[n] );
    }
*/
	printf( "Mittlere Aussentemperatur ueber 36h: %5.2f, index = %d\n", Tau_36h_mittel_f, index );
#endif
}

void cntrl_Solarbeheizung( void )
{
    if( SOL_KOLL_T_MW < sol_koll_t_max ) {
		/* Die Kollektortemperatur liegt unter dem Maximalwert  */
		if( SOL_KOLL_T_MW > ( SOL_SP1_Tu_MW + sol_dt_ein_sw ) ) {
            SOL_SP1_AV_SB = IO_AUF;
            SOL_PU_SB     = IO_EIN;
        }
        else {
            if( SOL_KOLL_T_MW <= ( SOL_SP1_Tu_MW + sol_dt_aus_sw ) ) {
                SOL_SP1_AV_SB = IO_ZU;
                SOL_PU_SB     = IO_AUS;
            }
            else {
                SOL_SP1_AV_SB = IO_AUF;
                SOL_PU_SB     = IO_EIN;
            }
        }

        if( SOL_KOLL_T_MW > ( SOL_SP2_Tu_MW + sol_dt_ein_sw ) ) {
            SOL_SP2_AV_SB = IO_AUF;
            SOL_PU_SB     = IO_EIN;
        }
        else {
            if( SOL_KOLL_T_MW <= ( SOL_SP2_Tu_MW + sol_dt_aus_sw ) ) {
                SOL_SP2_AV_SB = IO_ZU;
                SOL_PU_SB     = IO_AUS;
            }
            else {
                SOL_SP2_AV_SB = IO_AUF;
                SOL_PU_SB     = IO_EIN;
            }
        }
    }
    else {
        /* Bei Kollektortemperaturen ueber dem Maximalwert Solarkreis abschalten */
        SOL_PU_SB     = IO_AUS;
    }
}

/* Regler fuer den Waermetauscher, der den Heizkoerperheizkreis beheizt */
void cntrl_HK_Heizkreis( void )
{
    float           xd;     /* Regelabweichung */
    static float    xd_alt = 0.0;
    static float    hk_mv_y_alt_f = 50.0;
    float           q0, q1;
    const float     TA = 1.0;    /* Abtastzeit in sec                           */

    /* Vorlauftemperatursollwert im Floatformat berechnen */
    hk_Tvl_SW_f = toGradCelsius(hk_tr_sw - ALL_Tau_MW) * hk_tvl_steigung +
                  toGradCelsius(hk_tr_sw) + hk_tvl_niveau;
    if( (z_HK_Zustand == zAbgesenkt) && (partytime_flg == RESET) ) {
        hk_Tvl_SW_f -= toGradCelsius(hk_tvl_absenk);
    }
    if( hk_Tvl_SW_f < toGradCelsius(hk_tvl_min) ) {
        hk_Tvl_SW_f = toGradCelsius(hk_tvl_min);
    }
    else if( hk_Tvl_SW_f > toGradCelsius(hk_tvl_max) ) {
        hk_Tvl_SW_f = toGradCelsius(hk_tvl_max);
    }

    /* Regelabweichung Soll - Ist */
    xd = hk_Tvl_SW_f - toGradCelsius(HK_Tvl_MW);
    // hk_mv_y_f = 50.0 + hk_reg_kp*xd; /* reiner P-Regler */
    /* Mischventil ueber PI-Regler ansteuern */
    q0 =  hk_reg_kp + TA/(60.0*hk_reg_tn);
    q1 = -hk_reg_kp;
	hk_mv_y_f = hk_mv_y_alt_f + q0*xd + q1*xd_alt ;
    hk_mv_y_alt_f = hk_mv_y_f;
    xd_alt = xd;

    if( hk_mv_y_f >= 99.0 ) {
        // ProzentToAnalogOut( 99.0 , (ao_0_10V_t*) &HK_MV_Y );
        hk_mv_y_f = 99.0;
        hk_mv_y_alt_f = 99.0;
    }
    else if( hk_mv_y_f <= 1.0 ) {
        // ProzentToAnalogOut( 1.0 , (ao_0_10V_t*) &HK_MV_Y );
        hk_mv_y_f = 1.0;
        hk_mv_y_alt_f = 1.0;
    }

    /* Mischventil mit 0-10V ansteuern */
    ProzentToAnalogOut( hk_mv_y_f , (ao_0_10V_t*) &HK_MV_Y );

#ifdef __DEBUG__
    printf( "Heizkoerper Vorlauftemperatur Sollwert  = %5.2f\n", hk_Tvl_SW_f );
    printf( "Heizkoerper Vorlauftemperatur Istwert   = %5.2f\n", toGradCelsius(HK_Tvl_MW) );
    printf( "Regelabweichung der Vorlauftemperatur   = %5.2f\n", xd );
    printf( "Stellgroesse (float)                    = %5.2f\n", hk_mv_y_f );
#endif

    if( ( (Tau_36h_mittel_f <  toGradCelsius(all_at_start)) ||
          /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (ALL_Tau_MW       <  all_frostschutz            ) ||
          /* Die Aussentemperatur liegt unter der Frostschutzmarke          */
          (partytime_flg    == SET)
        ) && (hk_mv_y_f > 5.0) ) {
        HK_PU_SB = IO_EIN; /* Heizkreis Pumpe einschalten */
#ifdef __DEBUG__
        printf( "Heizkreispumpe eingeschaltet\n" );
#endif
    }
    else if( (Tau_36h_mittel_f > (toGradCelsius(all_at_start)+1.0)) ) {
        HK_PU_SB = IO_AUS;     /* Heizkreis Pumpe ausschalten */
/*       #ifdef __DEBUG__
            printf( "Heizkreispumpe ausgeschaltet\n" );
        #endif
*/
    }
    else {
        HK_PU_SB = IO_EIN; /* Heizkreis Pumpe einschalten */
    }
}

void cntrl_WW_Heizkreis( void )
{
//	static int      old_ww_wz_mw = IO_AUS; /* Merker fuer vorhergehenden Status Wasserzaehlerimpuls */
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
	}
	else {
		WW_ZIRK_PU_SB = IO_AUS;
    }

    if( (z_Zirk_Zustand == zEin) || (ALL_Tau_MW < all_frostschutz) ) {
        WW_HZG_PU_SB = IO_EIN;
    }
    else {
        WW_HZG_PU_SB = IO_AUS;
    }

    xd_pu = toGradCelsius(ww_tww_sw)-toGradCelsius(WW_Tww_MW);
    /* Berechnung von q0 und q1:*/
    q0 =  ww_hzg_reg_kp + TA/(60.0*ww_hzg_reg_tn);
    q1 = -ww_hzg_reg_kp;
	ww_hzg_pu_y_f = ww_hzg_pu_y_alt_f + q0*xd_pu + q1*xd_pu_alt;
    // ww_hzg_pu_y_f = 10.0 + ww_hzg_reg_kp*xd_pu; /* urspr. P-Regler */
    xd_pu_alt = xd_pu;
    ww_hzg_pu_y_alt_f = ww_hzg_pu_y_f;

    if( ww_hzg_pu_y_f <= 11.0 ) {
        ww_hzg_pu_y_f = 11.0;
        ww_hzg_pu_y_alt_f = 11.0;
    }
    else if( ww_hzg_pu_y_f >= 99.0 ) {
        ww_hzg_pu_y_f = 99.0;
        ww_hzg_pu_y_alt_f = 99.0;
    }

    ProzentToAnalogOut( ww_hzg_pu_y_f, (ao_0_10V_t *) &WW_HZG_PU_Y );

#ifdef __DEBUG__
    printf( "ww_hzg_reg_kp    = %5.1f \n", ww_hzg_reg_kp );
    printf( "ww_hzg_reg_tn    = %5.3f \n", ww_hzg_reg_tn );

    printf( "Warmwasser Pumpenstellwert     = %5.1f \n", ww_hzg_pu_y_f );
    printf( "Warmwasser Pumpenstellwert alt = %5.1f \n", ww_hzg_pu_y_alt_f );
    printf( "Warmwasser Temperatur          = %5.1f \n", toGradCelsius(WW_Tww_MW)  );
    printf( "Warmwasser Regelabw.r          = %5.1f \n", xd_pu );
    printf( "Warmwasser Vorlauftemperatur   = %5.1f \n", toGradCelsius(WW_HZG_Tvl_MW) );
#endif
}

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
	// fb_prim_mv_y_f = 50.0 + fb_reg_kp*xd;   /* reiner P-Regler Algorithmus */
	fb_prim_mv_y_alt_f = fb_prim_mv_y_f;
    xd_alt = xd;

    /* Mischventil mit 0-10V ansteuern */
    if( fb_prim_mv_y_f <= 1.0 ) {
        // ProzentToAnalogOut( 1.0, (ao_0_10V_t*) &FB_PRIM_MV_Y );
        fb_prim_mv_y_f = 1.0;
        fb_prim_mv_y_alt_f = 1.0;
    }
    else if( fb_prim_mv_y_f >= 99.0 ) {
        // ProzentToAnalogOut( 99.0, (ao_0_10V_t*) &FB_PRIM_MV_Y );
        fb_prim_mv_y_f = 99.0;
        fb_prim_mv_y_alt_f = 99.0;
    }

    ProzentToAnalogOut( fb_prim_mv_y_f , (ao_0_10V_t*) &FB_PRIM_MV_Y );

#ifdef __DEBUG__
    printf( "Fussbodenheizung Vorlauftemperatur Sollwert  = %5.2f\n", fb_Tvl_SW_f );
    printf( "Fussbodenheizung Vorlauftemperatur Istwert   = %5.2f\n", toGradCelsius(FB_SEK_Tvl_MW) );
    printf( "Regelabweichung der Vorlauftemperatur        = %5.2f\n", xd );
    printf( "Stellgroesse (float)                         = %5.2f\n", fb_prim_mv_y_f );
#endif

    if( ( (Tau_36h_mittel_f <  toGradCelsius(all_at_start)) || /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (ALL_Tau_MW       <  all_frostschutz            ) || /* Die Aussentemperatur liegt unter der Frostschutzmarke          */
          (partytime_flg    == SET)
        ) /* && (fb_prim_mv_y_f > 5.0) */ ) {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
    }
	else if( ( (Tau_36h_mittel_f > (toGradCelsius(all_at_start)+1.0)) ||
               (FB_SEK_TW == IO_EIN)
              ) /* && (fb_prim_mv_y_f < 1.0) */ ) {
        FB_PRIM_PU_SB = IO_AUS;
        FB_SEK_PU_SB  = IO_AUS;
    }
    else {
        FB_PRIM_PU_SB = IO_EIN;
        FB_SEK_PU_SB  = IO_EIN;
    }
}

void cntrl_Speicher1( void )
{
    kes_Tvl_SW_Sp1_f = toGradCelsius(sol_sp1_t_min + kes_sp_dt_sw);

#ifdef __DEBUG__
    printf( "kes_Tvl_SW_Sp1_f = %5.2f\n", kes_Tvl_SW_Sp1_f );
    printf( "SOL_SP1_To_MW = %d\n", SOL_SP1_To_MW );
    printf( "partytime_flg = %d\n", partytime_flg );
    printf( "sol_sp1_t_min = %d\n", sol_sp1_t_min );
#endif

    if( SOL_SP1_To_MW < sol_sp1_t_min ) {
        if( (z_Duschzeit == zJa) || (partytime_flg == SET) ) {
#ifdef __DEBUG__
            printf( "Pumpe Sp1 EIN!\n" );
#endif
            KES_PU_SP1_SB = IO_EIN;
        }
        else {
#ifdef __DEBUG__
            printf( "Pumpe Sp1 AUS!\n" );
#endif
            KES_PU_SP1_SB = IO_AUS;
        }
    }
    else {  /* if( SOL_SP1_To_MW >= sol_sp1_t_min ) { */
        KES_PU_SP1_SB = IO_AUS;
#ifdef __DEBUG__
        printf( "Pumpe Sp1 AUS!\n" );
#endif

    }

    if( hk_mv_y_f > 95.0 ) { /* Wenn HK Mischventil > 95% */
        /* Problem wenn Heizkreis zu hohe Anforderung hat */
        KES_PU_SP1_SB = IO_EIN;
#ifdef __DEBUG__
        printf( "Pumpe Sp1 EIN!\n" );
#endif
    }
}

void cntrl_Speicher2( void )
{
#ifdef __DEBUG__
    printf( "kes_Tvl_SW_Sp2_f = %5.2f\n", kes_Tvl_SW_Sp2_f );
    printf( "SOL_SP2_To_MW = %d\n", SOL_SP2_To_MW );
#endif

    kes_Tvl_SW_Sp2_f = fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw);
    printf( "kes_Tvl_SW_Sp2_f = %5.2f\n", kes_Tvl_SW_Sp2_f );

    if( toGradCelsius(SOL_SP2_To_MW) < fb_Tvl_SW_f ) {
        KES_PU_SP2_SB = IO_EIN;
#ifdef __DEBUG__
        printf( "Pumpe SP 2 EIN!\n" );
#endif
    }
    else if( toGradCelsius(SOL_SP2_To_MW) >= (fb_Tvl_SW_f + toGradCelsius(kes_sp_dt_sw)) ) {
        KES_PU_SP2_SB = IO_AUS;
#ifdef __DEBUG__
        printf( "Pumpe SP 2 AUS!\n" );
#endif
    }
}

void cntrl_Kessel( void )
{
    /* Sollwertvorgabe für den Kessel:
     * %-Zahl entspricht Vorlauftemperatur in °C
     * 100% entspr. 100°C
     * 10%  entpsr.  10°C
     * Werte kleiner 10%: Kessel ist abgeschaltet
     */

    if( KES_PU_SP1_SB >= IO_EIN ) {
        printf( "Kessel auf %5.1f gestellt\n", kes_Tvl_SW_Sp1_f  );
        ProzentToAnalogOut( kes_Tvl_SW_Sp1_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
    else if( KES_PU_SP2_SB >= IO_EIN ) {
       printf( "Kessel auf %5.1f gestellt\n", kes_Tvl_SW_Sp2_f  );
       ProzentToAnalogOut( kes_Tvl_SW_Sp2_f, (ao_0_10V_t*) &KES_Tvl_Y );
    }
    else {
        printf( "Kessel auf 0 gestellt\n" );
        ProzentToAnalogOut( 0.0, (ao_0_10V_t*) &KES_Tvl_Y );
    }
}

int cntrl_zeitprogramm( void )
{
	time_t		aktZeit;
	struct tm	*aktZeitElemente_p;
	int			aktSec, aktMin, aktHour, aktUhrzeit;
	int 		i;
	static int	oldSec=0, oldMin=0, oldHour=0;

#ifdef __MODULTEST__
    printf( "Uhrzeit Stunde: " ); scanf( "%d", &aktHour );
    printf( "Uhrzeit Minute: " ); scanf( "%d", &aktMin );
#else
	time( &aktZeit );
	aktZeitElemente_p = localtime( &aktZeit );
	aktHour 	      = aktZeitElemente_p->tm_hour;
	aktMin  	      = aktZeitElemente_p->tm_min;
    aktSec            = aktZeitElemente_p->tm_sec;
#endif

	aktUhrzeit 	= TAGESZEIT(aktHour, aktMin);

	/* Flags fuer nur alle Sekunden, Minuten bzw. einmal pro Stunde auszufuehrende Tasks nach Ablauf setzen */
	if( oldSec != aktSec ) {
		schedule_sec_flg = SET;
	}
	oldSec = aktSec;

	if( oldMin != aktMin ) {
		schedule_min_flg = SET;
	}
	oldMin = aktMin;

	if( oldHour != aktHour ) {
		schedule_hour_flg = SET;
	}
	oldHour = aktHour;

	/* Betriebszustand Heizkoerperheizkreis */
	for( i=0; i<hk_states; i++ ) {
		if( aktUhrzeit <= HK_Aus_Schaltzeiten[i] ) break;
	}
    if( (aktUhrzeit > HK_Ein_Schaltzeiten[i]) && (aktUhrzeit <= HK_Aus_Schaltzeiten[i]) ) {
        z_HK_Zustand = zNormal;
    }
    else {
        z_HK_Zustand = zAbgesenkt;
    }

	/* Betriebszustand Fussbodenheizkreis */
	for( i=0; i<fb_states; i++ ) {
        if( aktUhrzeit <= FB_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > FB_Ein_Schaltzeiten[i]) && (aktUhrzeit <= FB_Aus_Schaltzeiten[i]) ) {
        z_FB_Zustand = zNormal;
    }
    else {
        z_FB_Zustand = zAbgesenkt;
    }

	/* Betriebszustand Zirkulationspumpe */
	for( i=0; i<zirk_states; i++ ) {
        if( aktUhrzeit <= ZIRK_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > ZIRK_Ein_Schaltzeiten[i]) && (aktUhrzeit <= ZIRK_Aus_Schaltzeiten[i]) ) {
        z_Zirk_Zustand = zEin;
    }
    else {
        z_Zirk_Zustand = zAus;
    }

	/* Freigabe Speicherpumpe 1 */
	for( i=0; i<sp1_states; i++ ) {
        if( aktUhrzeit <= SP1_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > SP1_Ein_Schaltzeiten[i]) && (aktUhrzeit <= SP1_Aus_Schaltzeiten[i]) ) {
        z_SP1_Freigabe = zFreigegeben;
    }
    else {
        z_SP1_Freigabe = zGesperrt;
    }

	/* Freigabe Speicherpumpe 2 */
	for( i=0; i<sp2_states; i++ ) {
        if( aktUhrzeit <= SP2_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > SP2_Ein_Schaltzeiten[i]) && (aktUhrzeit <= SP2_Aus_Schaltzeiten[i]) ) {
        z_SP2_Freigabe = zFreigegeben;
    }
    else {
        z_SP2_Freigabe = zGesperrt;
    }

	/* Bootshausnutzung */
	for( i=0; i<haus_states; i++ ) {
        if( aktUhrzeit <= HAUS_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > HAUS_Ein_Schaltzeiten[i]) && (aktUhrzeit <= HAUS_Aus_Schaltzeiten[i]) ) {
        z_Bootshausnutzung = zJa;
    }
    else {
        z_Bootshausnutzung = zNein;
    }

	/* Duschzeit */
	for( i=0; i<dusch_states; i++ ) {
        if( aktUhrzeit <= DUSCH_Aus_Schaltzeiten[i] ) break;
    }
    if( (aktUhrzeit > DUSCH_Ein_Schaltzeiten[i]) && (aktUhrzeit <= DUSCH_Aus_Schaltzeiten[i]) ) {
        z_Duschzeit = zJa;
    }
    else {
        z_Duschzeit = zNein;
    }
}

void cntrl_initAverageTau( temp10_pt1000_t currTau )
{
	int i;

	for( i=0; i<60; i++ ) {
        Tau_1min_Intervall[i] = currTau;
	}
	for( i=0; i<MAX_ALL_Tau_mittel_Zeit; i++ ) {
        Tau_1h_mittel_36h_Intervall[i] = toGradCelsius( currTau );
	}
	Tau_1h_Summe_sl = currTau * 60;
	Tau_36h_Summe_f = toGradCelsius( currTau ) * MAX_ALL_Tau_mittel_Zeit;
}

/* Logging aller Messwerte und wichtigen Parameter in eine Datei */
void log_variables( FILE *fp )
{
	time_t	aktZeit;
    char    *time_str;

	time( &aktZeit );
    time_str = asctime( localtime( &aktZeit ) );
    fprintf( fp, "%24s  ALL_Tau_MW    = %5.1f C\n", time_str, toGradCelsius( ALL_Tau_MW ) );
    fprintf( fp, "%24s  SOL_KOLL_T_MW = %5.1f C\n", time_str, toGradCelsius( SOL_KOLL_T_MW ) );
    fprintf( fp, "%24s  SOL_SP1_Tu_MW = %5.1f C\n", time_str, toGradCelsius( SOL_SP1_Tu_MW ) );
    fprintf( fp, "%24s  SOL_SP1_To_MW = %5.1f C\n", time_str, toGradCelsius( SOL_SP1_To_MW ) );
    fprintf( fp, "%24s  SOL_SP2_Tu_MW = %5.1f C\n", time_str, toGradCelsius( SOL_SP2_Tu_MW ) );
    fprintf( fp, "%24s  SOL_SP2_To_MW = %5.1f C\n", time_str, toGradCelsius( SOL_SP2_To_MW ) );
    fprintf( fp, "%24s  KES_Tvl_MW    = %5.1f C\n", time_str, toGradCelsius( KES_Tvl_MW ) );
    fprintf( fp, "%24s  KES_Trl_MW    = %5.1f C\n", time_str, toGradCelsius( KES_Trl_MW ) );
    fprintf( fp, "%24s  HK_Tvl_MW     = %5.1f C\n", time_str, toGradCelsius( HK_Tvl_MW ) );
    fprintf( fp, "%24s  HK_Trl_MW     = %5.1f C\n", time_str, toGradCelsius( HK_Trl_MW ) );
    fprintf( fp, "%24s  WW_HZG_Tvl_MW = %5.1f C\n", time_str, toGradCelsius( WW_HZG_Tvl_MW ) );
    fprintf( fp, "%24s  WW_HZG_Trl_MW = %5.1f C\n", time_str, toGradCelsius( WW_HZG_Trl_MW ) );
    fprintf( fp, "%24s  WW_Tww_MW     = %5.1f C\n", time_str, toGradCelsius( WW_Tww_MW ) );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  FB_PRIM_Trl_MW = %5.1f C\n", time_str, toGradCelsius( FB_PRIM_Trl_MW ) );
    fprintf( fp, "%24s  FB_SEK_Tvl_MW  = %5.1f C\n", time_str, toGradCelsius( FB_SEK_Tvl_MW ) );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  all_Partyzeit_i  = %d\n", time_str, all_Partyzeit_i );
    fprintf( fp, "%24s  kes_Tvl_SW_Sp1_f = %5.1f C\n", time_str, kes_Tvl_SW_Sp1_f );
    fprintf( fp, "%24s  kes_Tvl_SW_Sp2_f = %5.1f C\n", time_str, kes_Tvl_SW_Sp2_f );
    fprintf( fp, "%24s  hk_Tvl_SW_f      = %5.1f C\n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "%24s  fb_Tvl_SW_f      = %5.1f C\n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  Tau_1h_mittel_f  = %6.2f C\n", time_str, Tau_1h_mittel_f );
    fprintf( fp, "%24s  Tau_36h_mittel_f = %6.2f C\n", time_str, Tau_36h_mittel_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  KES_PU_SP1_SB = %d \n", time_str, KES_PU_SP1_SB );
    fprintf( fp, "%24s  KES_PU_SP2_SB = %d \n", time_str, KES_PU_SP2_SB );
    fprintf( fp, "%24s  KES_Tvl_Y = %d \n", time_str, KES_Tvl_Y );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  FB_PRIM_MV_Y = %d \n", time_str,  FB_PRIM_MV_Y  );
    fprintf( fp, "%24s  FB_PRIM_PU_SB = %d \n", time_str, FB_PRIM_PU_SB  );
    fprintf( fp, "%24s  FB_SEK_PU_SB = %d \n", time_str, FB_SEK_PU_SB  );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  WW_HZG_MV_Y = %d \n", time_str, WW_HZG_MV_Y  );
    fprintf( fp, "%24s  WW_HZG_VV_SB = %d \n", time_str, WW_HZG_VV_SB );
    fprintf( fp, "%24s  WW_HZG_PU_SB = %d \n", time_str, WW_HZG_PU_SB  );
    fprintf( fp, "%24s  WW_ZIRK_PU_SB = %d \n", time_str, WW_ZIRK_PU_SB );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  HK_PU_SB = %d \n", time_str, HK_PU_SB );
    fprintf( fp, "%24s  HK_MV_Y = %d \n", time_str,  HK_MV_Y );
    fprintf( fp, "%24s  hk_Tvl_SW_f = %f \n", time_str, hk_Tvl_SW_f );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  WW_PARTY = %d \n", time_str, WW_PARTY );
    fprintf( fp, "%24s  STOERUNG = %d \n", time_str,  STOERUNG );
    fprintf( fp, "%24s  CONTROL_AKTIV = %d \n", time_str, CONTROL_AKTIV );
    fprintf( fp, "\n" );
    fprintf( fp, "%24s  KES_SSM = %d \n", time_str, KES_SSM );
    fprintf( fp, "%24s  KES_BR_BM = %d \n", time_str, KES_BR_BM );
    fprintf( fp, "\n" );
}



#ifdef __MAIN__
#if ( __DEBUG__ == 0 )

int main( void )
{
    init_parameters();
	init_variables();
	init_zeitprogramm();
    ALL_Tau_MW = 200;
    cntrl_initAverageTau( ALL_Tau_MW );
    ALL_Tau_MW = 210;

#ifdef __MODULTEST__
#if (TEST == 1)
    while( 1 ) {
        cntrl_zeitprogramm();
        printf( "z_HK_Zustand = %d\n", z_HK_Zustand );
        printf( "z_FB_Zustand = %d\n", z_FB_Zustand );
        printf( "z_Zirk_Zustand = %d\n", z_Zirk_Zustand );
        printf( "z_SP1_Freigabe = %d\n", z_SP1_Freigabe );
        printf( "z_SP2_Freigabe = %d\n", z_SP2_Freigabe );
        printf( "z_Bootshausnutzung = %d\n", z_Bootshausnutzung );
        printf( "z_Duschzeit = %d\n", z_Duschzeit );
    }
#endif
#if (TEST == 2)
    while( 1 ) {
        // cntrl_zeitprogramm();
        printf( "SOL_KOLL_T_MW (in 1/10 C) = " ); scanf( "%d", &SOL_KOLL_T_MW );
        printf( "SOL_SP1_Tu_MW (in 1/10 C) = " ); scanf( "%d", &SOL_SP1_Tu_MW );
        printf( "SOL_SP2_Tu_MW (in 1/10 C) = " ); scanf( "%d", &SOL_SP2_Tu_MW );
        cntrl_Solarbeheizung();
        printf( "SOL_SP1_AV_SB = %d\n", SOL_SP1_AV_SB );
        printf( "SOL_SP2_AV_SB = %d\n", SOL_SP1_AV_SB );
        printf( "SOL_PU_SB = %d\n", SOL_PU_SB );
    }
#endif
#endif /* __MODULTEST__ */
	while( 1 ) {
		cntrl_task();
        // sleep(1);
    }
}

#else /* __DEBUG__ */

int main( void )
{
    int prog_state_toggle;

    init_parameters();
	init_variables();
	init_zeitprogramm();
#ifdef __WAGO__
	KbusOpen();
	KbusUpdate();
#endif
	cntrl_initAverageTau( ALL_Tau_MW );

	/*  Hauptschleife (endlos) */
	while( 1 ) {
		if( prog_state_toggle == IO_AUS ) prog_state_toggle = IO_EIN;
		else prog_state_toggle = IO_AUS;
		// prog_state_toggle == IO_AUS ? prog_state_toggle = IO_EIN : prog_state_toggle = IO_AUS;
        CONTROL_AKTIV = prog_state_toggle;

        /* Sammeltask mit allen Reglerfunktionen aufrufen */
		cntrl_task();

		/* Sleep() funktioniert nur unter UNIX/Linux, nicht unter Windows */
		sleep(1);
	}
#ifdef __WAGO__
	KbusClose();
#endif
}

#endif /* __DEBUG__ */
#endif /* __MAIN__ */

