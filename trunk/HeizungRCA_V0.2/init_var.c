/* Debug Schalter:   */
// #define __MODULTEST__
// #define TEST 1

#define _INIT_VAR_C_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <string.h>
#include <time.h>

#include "vorgabe.h"
#include "variablen.h"
#include "zeitprogramm.h"

/* Prototypen */
int init_parameters( void );
int read_vorgaben( FILE *handle );
int init_zeitprogramm( void );
void init_variables( void );

int init_parameters( void )
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

		ww_hzg_reg_kp = 		WW_HZG_REG_Kp;
		ww_hzg_reg_tn = 		WW_HZG_REG_Tn;
		ww_tww_tvl_faktor =   	WW_Tww_Tvl_Faktor;
		ww_tz_sw = 				WW_Tz_SW;
	}
	else {
#ifdef __DEBUG__
    printf( "DEBUG: Ini Datei einlesen:\n" );
#endif
    read_vorgaben( handle );
	}
	fclose( handle );
    return( -1 );
}

int read_vorgaben( FILE *handle )
{
	char	linestr[128];
	char	*parameter, *value;

	while( !feof( handle ) )  {
        fgets( linestr, 127, handle );

#ifdef __DEBUG__
        printf( "DEBUG: %s \n", linestr );
#endif
        if( linestr[0] != '%' ) {
            parameter = strtok( linestr, "=" );
#ifdef __DEBUG__
            printf( "DEBUG: parameter = \"%s\" \n", parameter );
#endif
            if( strncmp( parameter, "ALL_Tau_mittel_Zeit", 18 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &all_tau_mittel_zeit );
            }
            else if( strncmp( parameter, "ALL_Partydauer", 14 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &all_partydauer );
            }
            else if( strncmp( parameter, "ALL_Frostschutz", 15 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &all_frostschutz );
            }
            else if( strncmp( parameter, "ALL_AT_Start", 12 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &all_at_start );
            }
            else if( strncmp( parameter, "SOL_dT_ein_SW", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &sol_dt_ein_sw );
            }
            else if( strncmp( parameter, "SOL_dT_aus_SW", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &sol_dt_aus_sw );
            }
            else if( strncmp( parameter, "SOL_KOLL_T_max", 14 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &sol_koll_t_max );
            }
            else if( strncmp( parameter, "SOL_SP_T_max", 12 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &sol_sp_t_max );
            }
            else if( strncmp( parameter, "SOL_SP1_T_min", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &sol_sp1_t_min );
            }
            else if( strncmp( parameter, "KES_SP_dT_SW", 12 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &kes_sp_dt_sw );
            }
            else if( strncmp( parameter, "HK_Tvl_Steigung", 15 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &hk_tvl_steigung );
            }
            else if( strncmp( parameter, "HK_Tvl_Niveau", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &hk_tvl_niveau );
            }
            else if( strncmp( parameter, "HK_Tvl_Absenk", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &hk_tvl_absenk );
            }
            else if( strncmp( parameter, "HK_Tvl_Min", 10 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &hk_tvl_min );
            }
            else if( strncmp( parameter, "HK_Tvl_Max", 10 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &hk_tvl_max );
            }
            else if( strncmp( parameter, "HK_Frostschutz", 14 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &hk_frostschutz );
            }
            else if( strncmp( parameter, "HK_REG_Kp", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &hk_reg_kp );
            }
            else if( strncmp( parameter, "HK_REG_Tn", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &hk_reg_tn );
            }
            else if( strncmp( parameter, "HK_Tr_SW", 8 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &hk_tr_sw );
            }
            else if( strncmp( parameter, "FB_Tvl_Steigung", 15 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &fb_tvl_steigung );
            }
            else if( strncmp( parameter, "FB_Tvl_Niveau", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &fb_tvl_niveau );
            }
            else if( strncmp( parameter, "FB_Tr_SW", 8 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &fb_tr_sw );
            }
            else if( strncmp( parameter, "FB_Tvl_Absenk", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &fb_tvl_absenk );
            }
            else if( strncmp( parameter, "FB_Tvl_Min", 10 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &fb_tvl_min );
            }
            else if( strncmp( parameter, "FB_Tvl_Max", 10 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &fb_tvl_max );
            }
            else if( strncmp( parameter, "FB_REG_Kp", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &fb_reg_kp );
            }
            else if( strncmp( parameter, "FB_REG_Tn", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &fb_reg_tn );
            }
            else if( strncmp( parameter, "WW_Tww_SW", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &ww_tww_sw );
            }
            else if( strncmp( parameter, "WW_Tww_Max", 10 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &ww_tww_max );
            }
            else if( strncmp( parameter, "WZ_Faktor", 9 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &wz_faktor );
            }
            else if( strncmp( parameter, "WZ_Max", 6 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &wz_max );
            }
            else if( strncmp( parameter, "WW_HZG_REG_Kp", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &ww_hzg_reg_kp );
            }
            else if( strncmp( parameter, "WW_HZG_REG_Tn", 13 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &ww_hzg_reg_tn );
            }
            else if( strncmp( parameter, "WW_Tww_Tvl_Faktor", 17 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%f", &ww_tww_tvl_faktor );
            }
            else if( strncmp( parameter, "WW_Tz_SW", 8 ) == 0 ) {
                value = strtok( NULL, "\n" );
                sscanf( value, "%d", &ww_tz_sw );
            }
        }
    }
    return( -1 );
}

int init_zeitprogramm( void )
{
	FILE 	*handle;
   	char	linestr[128];
 	char	*parameter, *value;
    int     hour, min;

	handle = fopen( "/home/zeitprogramm.ini", "r" );
	if( handle == NULL ) {
        /* todo */
    }
    else {
		while( !feof( handle ) )  {
            fgets( linestr, 127, handle );
            #ifdef __DEBUG__
            printf( "DEBUG: linestr = %s", linestr );
            #endif
            if( linestr[0] != '%' ) {
                parameter = strtok( linestr, "=" );
                #ifdef __DEBUG__
                printf( "DEBUG: parameter = \"%s\" \n", parameter );
                #endif
                if( strncmp( parameter, "HK_EIN", 6 ) == 0 ) {
                    hk_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( hk_states < HK_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                HK_Ein_Schaltzeiten[hk_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         hk_states, HK_Ein_Schaltzeiten[hk_states] );
                                #endif
                                hk_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: hk_states = %d \n", hk_states );
                    #endif
                }
                else if( strncmp( parameter, "HK_AUS", 6 ) == 0 ) {
                    hk_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( hk_states < HK_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                HK_Aus_Schaltzeiten[hk_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         hk_states, HK_Aus_Schaltzeiten[hk_states] );
                                #endif
                                hk_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: hk_states = %d \n", hk_states );
                    #endif
                }
                else if( strncmp( parameter, "FB_EIN", 6 ) == 0 ) {
                    fb_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( fb_states < FB_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                FB_Ein_Schaltzeiten[fb_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         fb_states, FB_Ein_Schaltzeiten[fb_states] );
                                #endif
                                fb_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: fb_states = %d \n", fb_states );
                    #endif
                }
                else if( strncmp( parameter, "FB_AUS", 6 ) == 0 ) {
                    fb_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( fb_states < FB_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                FB_Aus_Schaltzeiten[fb_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         fb_states, FB_Aus_Schaltzeiten[fb_states] );
                                #endif
                                fb_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: fb_states = %d \n", fb_states );
                    #endif
                }
                else if( strncmp( parameter, "ZIRK_EIN", 8 ) == 0 ) {
                    zirk_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( zirk_states < ZIRK_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                ZIRK_Ein_Schaltzeiten[zirk_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         zirk_states, ZIRK_Ein_Schaltzeiten[zirk_states] );
                                #endif
                                zirk_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: zirk_states = %d \n", zirk_states );
                    #endif
                }
                else if( strncmp( parameter, "ZIRK_AUS", 8 ) == 0 ) {
                    zirk_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( zirk_states < ZIRK_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                ZIRK_Aus_Schaltzeiten[zirk_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         zirk_states, ZIRK_Aus_Schaltzeiten[zirk_states] );
                                #endif
                                zirk_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: zirk_states = %d \n", zirk_states );
                    #endif
                }
                else if( strncmp( parameter, "SP1_EIN", 7 ) == 0 ) {
                    sp1_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( sp1_states < SP1_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                SP1_Ein_Schaltzeiten[sp1_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         sp1_states, SP1_Ein_Schaltzeiten[sp1_states] );
                                #endif
                                sp1_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: sp1_states = %d \n", sp1_states );
                    #endif
                }
                else if( strncmp( parameter, "SP1_AUS", 7 ) == 0 ) {
                    sp1_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( sp1_states < SP1_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                SP1_Aus_Schaltzeiten[sp1_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         sp1_states, SP1_Aus_Schaltzeiten[sp1_states] );
                                #endif
                                sp1_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: sp1_states = %d \n", sp1_states );
                    #endif
                }
                else if( strncmp( parameter, "SP2_EIN", 7 ) == 0 ) {
                    sp2_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( sp2_states < SP2_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                SP2_Ein_Schaltzeiten[sp2_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         sp2_states, SP2_Ein_Schaltzeiten[sp2_states] );
                                #endif
                                sp2_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: sp2_states = %d \n", sp2_states );
                    #endif
                }
                else if( strncmp( parameter, "SP2_AUS", 7 ) == 0 ) {
                    sp2_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( sp2_states < SP2_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                SP2_Aus_Schaltzeiten[sp2_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         sp2_states, SP2_Aus_Schaltzeiten[sp2_states] );
                                #endif
                                sp2_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: sp2_states = %d \n", sp2_states );
                    #endif
                }
                else if( strncmp( parameter, "HAUS_EIN", 8 ) == 0 ) {
                    haus_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( haus_states < HAUS_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                HAUS_Ein_Schaltzeiten[haus_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         haus_states, HAUS_Ein_Schaltzeiten[haus_states] );
                                #endif
                                haus_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: haus_states = %d \n", haus_states );
                    #endif
                }
                else if( strncmp( parameter, "HAUS_AUS", 8 ) == 0 ) {
                    haus_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( haus_states < HAUS_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                HAUS_Aus_Schaltzeiten[haus_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         haus_states, HAUS_Aus_Schaltzeiten[haus_states] );
                                #endif
                                haus_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: haus_states = %d \n", haus_states );
                    #endif
                }
                else if( strncmp( parameter, "DUSCH_EIN", 9 ) == 0 ) {
                    dusch_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( dusch_states < DUSCH_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                DUSCH_Ein_Schaltzeiten[dusch_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESEINSCHALTZEIT[%d] = %d\n",
                                         dusch_states, DUSCH_Ein_Schaltzeiten[dusch_states] );
                                #endif
                                dusch_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: dusch_states = %d \n", dusch_states );
                    #endif
                }
                else if( strncmp( parameter, "DUSCH_AUS", 9 ) == 0 ) {
                    dusch_states = 0;
                    #ifdef __DEBUG__
                    printf( "DEBUG: value = \"%s\" \n", parameter );
                    #endif
                    while( dusch_states < DUSCH_STATES_MAX )  {
                        value = strtok( NULL, ":" );    /* Stundenteilstring */
                        if( value != NULL ) {
                            sscanf( value, "%d", &hour );
                            #ifdef __DEBUG__
                            printf( "DEBUG: hour = %d \n", hour );
                            #endif
                            value = strtok( NULL, ",;" );   /* Minutenteilstring */
                            if( value != NULL ) {
                                sscanf( value, "%d", &min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: min = %d \n", min );
                                #endif
                                DUSCH_Aus_Schaltzeiten[dusch_states] = TAGESZEIT( hour, min );
                                #ifdef __DEBUG__
                                printf( "DEBUG: TAGESAUSSCHALTZEIT[%d] = %d\n",
                                         dusch_states, DUSCH_Aus_Schaltzeiten[dusch_states] );
                                #endif
                                dusch_states ++;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    #ifdef __DEBUG__
                    printf( "DEBUG: dusch_states = %d \n", dusch_states );
                    #endif
                }
            }
        }
    }
}

void init_variables( void )
{
	int i;

	Tau_1h_Summe_sl   = 0;
	Tau_1h_mittel_f   = 0.0;
	Tau_36h_Summe_f   = 0.0;
	Tau_36h_mittel_f  = 0.0;
	schedule_min_flg  = RESET;
	schedule_hour_flg = RESET;
	partytime_flg     = RESET;
    minutes_since_party_pressed = 0;

	for( i=0; i<60; i++ ) {
		Tau_1min_Intervall[i] = 0;
	}
	for( i=0; i<MAX_ALL_Tau_mittel_Zeit; i++ ) {
		Tau_1h_mittel_36h_Intervall[i] = 0.0;
	}
}


#ifdef __MODULTEST__
/* Code fuer Modultests: */

/* Test von init_parameters() */
#if (TEST == 1)
int main()
{
    /* Test 1: Testen der Initialisierung ueber Parameterdatei */
	init_parameters();

	printf( "all_tau_mittel_zeit = %d\n", all_tau_mittel_zeit );
	printf( "all_partydauer = %d\n", all_partydauer );
	printf( "all_frostschutz = %d\n", all_frostschutz );
	printf( "all_at_start = %d\n", all_at_start );

	printf( "sol_dt_ein_sw = %d\n",	sol_dt_ein_sw );
	printf( "sol_dt_aus_sw = %d\n",	sol_dt_aus_sw );
	printf( "sol_koll_t_max = %d\n", sol_koll_t_max );
	printf( "sol_sp_t_max = %d\n", sol_sp_t_max );
	printf( "sol_sp1_t_min = %d\n", sol_sp1_t_min );

	printf( "kes_sp_dt_sw = %d\n", kes_sp_dt_sw );

	printf( "hk_tvl_steigung = %f\n", hk_tvl_steigung );
	printf( "hk_tvl_niveau = %f\n", hk_tvl_niveau );
	printf( "hk_tvl_absenk = %d\n", hk_tvl_absenk );
	printf( "hk_tvl_min = %d\n", hk_tvl_min );
	printf( "hk_tvl_max = %d\n", hk_tvl_max );
	printf( "hk_frostschutz = %d\n", hk_frostschutz );
	printf( "hk_reg_kp = %f\n", hk_reg_kp );
	printf( "hk_reg_tn = %f\n", hk_reg_tn );
	printf( "hk_tr_sw = %d\n", hk_tr_sw );

	printf( "fb_tvl_steigung = %f\n", fb_tvl_steigung );
	printf( "fb_tvl_niveau = %f\n", fb_tvl_niveau );
	printf( "fb_tr_sw = %d\n", fb_tr_sw );
	printf( "fb_tvl_absenk = %d\n", fb_tvl_absenk );
	printf( "fb_tvl_min = %d\n", fb_tvl_min );
	printf( "fb_tvl_max = %d\n", fb_tvl_max );

	printf( "fb_reg_kp = %f\n", fb_reg_kp );
	printf( "fb_reg_tn = %f\n", fb_reg_tn );

	printf( "ww_tww_sw = %d\n", ww_tww_sw );
	printf( "ww_tww_max = %d\n", ww_tww_max );
	printf( "wz_faktor = %f\n", wz_faktor );
	printf( "wz_max = %f\n", wz_max );

	printf( "ww_hzg_reg_kp = %f\n", ww_hzg_reg_kp );
	printf( "ww_hzg_reg_tn = %f\n", ww_hzg_reg_tn );
	printf( "ww_tww_tvl_faktor = %f\n", ww_tww_tvl_faktor );
	printf( "ww_tz_sw = %d\n", ww_tz_sw );
}
#endif

/* Test von init_zeitprogramm() */
#if (TEST == 2)
int main()
{
    int n;
    /* Test 2: Testen der Initialisierung des Zeitprogramms ueber zeitprogramm.ini */
 	init_zeitprogramm();

    for( n=0; n<hk_states; n++ ) {
        printf( "HK_Ein_Schaltzeiten[%d] = %d\n", n, HK_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<hk_states; n++ ) {
        printf( "HK_Aus_Schaltzeiten[%d] = %d\n", n, HK_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<fb_states; n++ ) {
        printf( "FB_Ein_Schaltzeiten[%d] = %d\n", n, FB_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<fb_states; n++ ) {
        printf( "FB_Aus_Schaltzeiten[%d] = %d\n", n, FB_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<zirk_states; n++ ) {
        printf( "ZIRK_Ein_Schaltzeiten[%d] = %d\n", n, ZIRK_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<zirk_states; n++ ) {
        printf( "ZIRK_Aus_Schaltzeiten[%d] = %d\n", n, ZIRK_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<sp1_states; n++ ) {
        printf( "SP1_Ein_Schaltzeiten[%d] = %d\n", n, SP1_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<sp1_states; n++ ) {
        printf( "SP1_Aus_Schaltzeiten[%d] = %d\n", n, SP1_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<sp2_states; n++ ) {
        printf( "SP2_Ein_Schaltzeiten[%d] = %d\n", n, SP2_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<sp2_states; n++ ) {
        printf( "SP2_Aus_Schaltzeiten[%d] = %d\n", n, SP2_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<haus_states; n++ ) {
        printf( "HAUS_Ein_Schaltzeiten[%d] = %d\n", n, HAUS_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<haus_states; n++ ) {
        printf( "HAUS_Aus_Schaltzeiten[%d] = %d\n", n, HAUS_Aus_Schaltzeiten[n] );
    }
    for( n=0; n<dusch_states; n++ ) {
        printf( "DUSCH_Ein_Schaltzeiten[%d] = %d\n", n, DUSCH_Ein_Schaltzeiten[n] );
    }
    for( n=0; n<dusch_states; n++ ) {
        printf( "DUSCH_Aus_Schaltzeiten[%d] = %d\n", n, HAUS_Aus_Schaltzeiten[n] );
    }
 }
 #endif

#endif

