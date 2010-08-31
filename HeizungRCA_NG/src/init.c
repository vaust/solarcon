#define _INIT_C_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "gen_types.h"

#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

#include "init.h"

/* Prototypen */
int init_Parameters( void );
int init_Vorgaben( FILE *handle );
int init_zeitprogramm( void );
int zeit_einlesen( int states_max, schaltpunkt_t schaltzeiten[]);
void init_variables( void );

int init_Parameters( void )
{
	FILE 	*handle;

	handle = fopen( "/home/vorgaben.ini", "r" );
	if( handle == NULL ) {
    /* Die Datei vorgaben.ini scheint nicht vorhanden zu sein:
     * Defaultwerte aus #defines in vorgabe.h initialisieren
	 */
		all_tau_mittel_zeit = 	ALL_Tau_mittel_Zeit;
		all_partydauer = 		ALL_Partydauer;
		all_frostschutz =	 	ALL_Frostschutz;
		all_at_start = 			ALL_AT_Start;

		sol_dt_ein_sw = 		SOL_dT_ein_SW;
		sol_dt_aus_sw = 		SOL_dT_aus_SW;
		sol_koll_t_max = 		SOL_KOLL_T_max;
		sol_sp_t_max = 			SOL_SP_T_max;
		sol_sp1_t_min = 		SOl_SP1_T_min,

		kes_sp_dt_sw = 			KES_SP_dT_SW;

		hk_tvl_steigung = 		HK_Tvl_Steigung;
		hk_tvl_niveau = 	  	HK_Tvl_Niveau;
		hk_tvl_absenk = 		HK_Tvl_Absenk;
		hk_tvl_min = 			HK_Tvl_Min;
		hk_tvl_max = 			HK_Tvl_Max;
		hk_frostschutz = 		HK_Frostschutz;
		hk_reg_kp = 			HK_REG_Kp;
		hk_reg_tn = 		  	HK_REG_Tn;
        hk_tr_sw  =             HK_Tr_SW;

		fb_tvl_steigung =		FB_Tvl_Steigung;
		fb_tvl_niveau = 		FB_Tvl_Niveau;
		fb_tr_sw =			  	FB_Tr_SW;
		fb_tvl_absenk = 		FB_Tvl_Absenk;
		fb_tvl_min = 			FB_Tvl_Min;
		fb_tvl_max = 			FB_Tvl_Max;

		fb_reg_kp = 			FB_REG_Kp;
		fb_reg_tn = 		  	FB_REG_Tn;

		ww_tww_sw = 			WW_Tww_SW;
		ww_tww_max = 			WW_Tww_Max;
		wz_faktor = 		  	WZ_Faktor;
		wz_max = 			 	Wz_Max;

		ww_pu_reg_kp = 		    WW_PU_REG_Kp;
		ww_pu_reg_tn = 		    WW_PU_REG_Tn;
		ww_tww_tvl_faktor =   	WW_Tww_Tvl_Faktor;
		ww_tz_sw = 				WW_Tz_SW;

        hour_offset =           1;
    }
	else {
#ifdef __DEBUG__
    printf( "DEBUG: Ini Datei einlesen:\n" );
#endif
    init_ReadVorgaben( handle );
	}
	fclose( handle );
    return( -1 );
}


int init_Vorgaben( FILE *handle )
{
	char	linestr[128];
	char	*parameter, *value;
    int     n;
    
	while( !feof( handle ) )  {
        fgets( linestr, 127, handle );
        if( linestr[0] != '%' ) {
            parameter = strtok( linestr, "=" );
            for( n=0; n<PARSE_SET_N; n++ ) {
                if( strncmp( parameter, Vorgaben[n].VarName, strlen(Vorgaben[n].VarName) ) == 0 ) {
                    value = strtok( NULL, "\n" );
                    sscanf( value, Vorgaben[n].format, Vorgaben[n].VarPointer );
                    break; /* Passende Variable gefunden: For Schleife abbrechen und zur naechsten Zeile */
                }
            }
        }
    }
    return( -1 );
}

int zeit_einlesen( int states_max, schaltpunkt_t schaltzeiten[])
{   int     states = 0;
    int     wday, hour, min;
    char    *value;

    while( states < states_max )  {
        value = strtok( NULL, "-" );    /* Wochentagteilstring */
        if( value != NULL ) {
            sscanf( value, "%d", &wday );
            value = strtok( NULL, ":" );   /* Stundenteilstring */
            if( value != NULL ) {
                sscanf( value, "%d", &hour );
                value = strtok( NULL, ",;" );   /* Minutenteilstring */
                if( value != NULL ) {
                    sscanf( value, "%d", &min );
                    schaltzeiten[states] = WOCHENZEIT( wday, hour, min );
                    states ++;
                }
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    return( states );
}

int init_zeitprogramm( void )
{
	FILE 	*handle;
   	char	linestr[128];
 	char	*parameter, *value;
    int     wday, hour, min;
    int     i;

	handle = fopen( "/home/wochenzeitprogramm.ini", "r" );
	if( handle == NULL ) {
        /* todo */
        printf( "Datei wochenzeitprogramm.ini konnte nicht geöffnet werden!\n" );
    }
    else {
		while( !feof( handle ) )  {
            fgets( linestr, 127, handle );
            if( linestr[0] != '%' ) {
                parameter = strtok( linestr, "=" );
                if( strncmp( parameter, "HK_EIN", 6 ) == 0 ) {
                    hk_states = zeit_einlesen(HK_STATES_MAX, HK_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "HK_AUS", 6 ) == 0 ) {
                    hk_states = zeit_einlesen(HK_STATES_MAX, HK_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "FB_EIN", 6 ) == 0 ) {
                    fb_states = zeit_einlesen(FB_STATES_MAX, FB_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "FB_AUS", 6 ) == 0 ) {
                    fb_states = zeit_einlesen(FB_STATES_MAX, FB_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "ZIRK_EIN", 8 ) == 0 ) {
                    zirk_states = zeit_einlesen(ZIRK_STATES_MAX, ZIRK_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "ZIRK_AUS", 8 ) == 0 ) {
                    zirk_states = zeit_einlesen(ZIRK_STATES_MAX, ZIRK_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "DUSCH_EIN", 9 ) == 0 ) {
                    dusch_states = zeit_einlesen(DUSCH_STATES_MAX, DUSCH_Ein_Schaltzeiten);
                }
                else if( strncmp( parameter, "DUSCH_AUS", 9 ) == 0 ) {
                    dusch_states = zeit_einlesen(DUSCH_STATES_MAX, DUSCH_Aus_Schaltzeiten);
                }
                else if( strncmp( parameter, "HOUR_OFFSET", 11 ) == 0 ) {
                    value = strtok( NULL, ";" );
                    sscanf( value, "%d", &hour_offset );
                }
            }
        }
    }
}

void init_variables( void )
{
	int i;

	Tau_1h_Summe_f    = 0.0;
	Tau_1h_mittel_f   = 0.0;
	Tau_36h_Summe_f   = 0.0;
	Tau_36h_mittel_f  = 0.0;
	schedule_min_flg  = RESET;
	schedule_hour_flg = RESET;
	partytime_flg     = RESET;
    all_party_restzeit_min = 0;
    ww_party_restzeit_min  = 0;

	for( i=0; i<60; i++ ) {
		Tau_1min_Intervall[i] = 0.0;
	}
	for( i=0; i<MAX_ALL_Tau_mittel_Zeit; i++ ) {
		Tau_1h_mittel_36h_Intervall[i] = 0.0;
	}
}


