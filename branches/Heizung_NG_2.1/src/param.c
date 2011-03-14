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

        param.all.tau_mittel_zeit = ALL_Tau_mittel_Zeit;
        param.all.partydauer =      ALL_Partydauer;
        param.all.frostschutz =     ALL_Frostschutz;
        param.all.at_start =        ALL_AT_Start;

        param.sol.dt_ein_sw =       SOL_dT_ein_SW;
        param.sol.dt_aus_sw =       SOL_dT_aus_SW;
        param.sol.koll_t_max =      SOL_KOLL_T_max;
        param.sol.sp_t_max =        SOL_SP_T_max;
        param.sol.sp1_t_min =       SOl_SP1_T_min,

        param.kes.sp_dt_sw =        KES_SP_dT_SW;

        param.hk.tvl.steigung =     HK_Tvl_Steigung;
        param.hk.tvl.niveau =       HK_Tvl_Niveau;
        param.hk.tvl.absenk =       HK_Tvl_Absenk;
        param.hk.tvl.min =          HK_Tvl_Min;
        param.hk.tvl.max =          HK_Tvl_Max;
        param.hk.frostschutz =      HK_Frostschutz;
        param.hk.reg.kp =           HK_REG_Kp;
        param.hk.reg.ki =           HK_REG_Ki;
        param.hk.reg.ap =           HK_REG_AP;
        param.hk.tr_sw  =           HK_Tr_SW;

        param.fb.tvl.steigung =     FB_Tvl_Steigung;
        param.fb.tvl.niveau =       FB_Tvl_Niveau;
        param.fb.tr_sw =            FB_Tr_SW;
        param.fb.tvl.absenk =       FB_Tvl_Absenk;
        param.fb.tvl.min =          FB_Tvl_Min;
        param.fb.tvl.max =          FB_Tvl_Max;

        param.fb.reg.kp =           FB_REG_Kp;
        param.fb.reg.ki =           FB_REG_Ki;
        param.fb.reg.ap =           FB_REG_AP;
        
        param.ww.tww_sw =           WW_Tww_SW;
        param.ww.tww_max =          WW_Tww_Max;
        param.ww.wz_faktor =        WZ_Faktor;
        param.ww.wz_max =           Wz_Max;

        param.ww.pu_reg.kp =        WW_PU_REG_Kp;
        param.ww.pu_reg.ki =        WW_PU_REG_Ki;
        param.ww.pu_reg.ap =        WW_PU_REG_AP;
        
        param.ww.mv_korr =          WW_MV_KORR;
        param.ww.tww_tvl_faktor =   WW_Tww_Tvl_Faktor;
        param.ww.tz_sw =            WW_Tz_SW;
        param.sys.zykluszeit =      ABTASTZEIT_USEC;
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


