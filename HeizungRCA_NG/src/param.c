#define _PARAM_C_

#include <stdio.h>
#include <string.h>
#include "gen_types.h"
#include "param.h"

static int param_ReadVorgaben( FILE *handle )
{
    char    linestr[128];
    char    *parameter, *value;
    int     n, errCode = 0;

    while( !feof( handle ) )  {
        fgets( linestr, 127, handle );
        if( linestr[0] != '%' ) {
            parameter = strtok( linestr, "=" );
            if( NULL != parameter ) {
                for( n=0; n<(sizeof(param_Vorgaben)/sizeof(parse_set_t)); n++ ) {
                    if( strncmp( parameter, param_Vorgaben[n].VarName, strlen(param_Vorgaben[n].VarName) ) == 0 ) {
                        value = strtok( NULL, "\n" );
                        if( NULL != value ) {
                            sscanf( value, param_Vorgaben[n].format, param_Vorgaben[n].VarPointer );
                        }
                        else {
                            errCode = STD_ERR;
                        }
                        break; /* Passende Variable gefunden: For Schleife abbrechen und zur naechsten Zeile */
                    }
                }
            }
            else {
                errCode = STD_ERR;
            }
        }
    }
    return(errCode);
}

int param_Init( void )
{
    FILE    *handle;
    int     errCode = 0;

    handle = fopen( VORGABENDATEI, "r" );
    if( handle == NULL ) {
        /* Die Datei vorgaben.ini scheint nicht vorhanden zu sein:
         * Defaultwerte aus #defines in vorgabe.h initialisieren
         */
        printf( "PARAM.C: Die Datei vorgaben.ini ist nicht vorhanden\n" );
        printf( "PARAM.C: Die Parameter werden mit Default Werten initialisiert!\n" );
        errCode = -1;

        param_all_tau_mittel_zeit = ALL_Tau_mittel_Zeit;
        param_all_partydauer =      ALL_Partydauer;
        param_all_frostschutz =     ALL_Frostschutz;
        param_all_at_start =        ALL_AT_Start;

        param_sol_dt_ein_sw =       SOL_dT_ein_SW;
        param_sol_dt_aus_sw =       SOL_dT_aus_SW;
        param_sol_koll_t_max =      SOL_KOLL_T_max;
        param_sol_sp_t_max =        SOL_SP_T_max;
        param_sol_sp1_t_min =       SOl_SP1_T_min,

        param_kes_sp_dt_sw =        KES_SP_dT_SW;

        param_hk_tvl_steigung =     HK_Tvl_Steigung;
        param_hk_tvl_niveau =       HK_Tvl_Niveau;
        param_hk_tvl_absenk =       HK_Tvl_Absenk;
        param_hk_tvl_min =          HK_Tvl_Min;
        param_hk_tvl_max =          HK_Tvl_Max;
        param_hk_frostschutz =      HK_Frostschutz;
        param_hk_reg_kp =           HK_REG_Kp;
        param_hk_reg_ki =           HK_REG_Ki;
        param_hk_reg_ap =           HK_REG_AP;
        param_hk_tr_sw  =           HK_Tr_SW;

        param_fb_tvl_steigung =     FB_Tvl_Steigung;
        param_fb_tvl_niveau =       FB_Tvl_Niveau;
        param_fb_tr_sw =            FB_Tr_SW;
        param_fb_tvl_absenk =       FB_Tvl_Absenk;
        param_fb_tvl_min =          FB_Tvl_Min;
        param_fb_tvl_max =          FB_Tvl_Max;

        param_fb_reg_kp =           FB_REG_Kp;
        param_fb_reg_ki =           FB_REG_Ki;
        param_fb_reg_ap =           FB_REG_AP;
        
        param_ww_tww_sw =           WW_Tww_SW;
        param_ww_tww_max =          WW_Tww_Max;
        param_wz_faktor =           WZ_Faktor;
        param_wz_max =              Wz_Max;

        param_ww_pu_reg_kp =        WW_PU_REG_Kp;
        param_ww_pu_reg_ki =        WW_PU_REG_Ki;
        param_ww_pu_reg_ap =        WW_PU_REG_AP;
        
        param_ww_mv_korr =          WW_MV_KORR;
        param_ww_tww_tvl_faktor =   WW_Tww_Tvl_Faktor;
        param_ww_tz_sw =            WW_Tz_SW;
        param_sys_zykluszeit =      ABTASTZEIT_USEC;
    }
    else {
        printf( "PARAM.C: Ini Datei einlesen:\n" );
        errCode = param_ReadVorgaben( handle );
    }
    fclose( handle );
    return( errCode );
}

/** TESTCODE  */
#ifdef __TEST__

void param_TEST_Vorgaben( void )
{
    int n;

    for( n=0; n<param_Vorgaben_len; n++ ) {
        printf( "PARAM.C: TEST: " );
        printf( param_Vorgaben[n].VarName );
        printf( " = " );
        switch ( param_Vorgaben[n].format[1] ) {
            case 'd':
                printf( param_Vorgaben[n].format, *(int *)param_Vorgaben[n].VarPointer );
                break;
            case 'f':
            default:
                printf( param_Vorgaben[n].format, *(float *)param_Vorgaben[n].VarPointer );
                break;
        }
        printf( "\n" );
    }
    printf( "PARAM.C: TEST: Sizeof(Vorgaben) = %lu\n\n", (sizeof(param_Vorgaben)/sizeof(parse_set_t)) );
}
#endif /* __TEST__ */


