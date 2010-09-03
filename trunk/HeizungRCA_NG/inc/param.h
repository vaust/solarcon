#ifndef _PARAM_H_
#define _PARAM_H_

/* <Defines> */

/* Vorgabewerte: */
#define ALL_Tau_mittel_Zeit       36    /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)        */
#define MAX_ALL_Tau_mittel_Zeit   48    /* max. Wert aus Kommentar in vorgaben.ini                                */
#define ALL_Partydauer           120    /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)        */
#define ALL_Frostschutz          3.0    /* Aussentemperatur unter der Heizkreis immer in Betrieb in °C            */
#define ALL_AT_Start            15.0    /* Aussentemperatur unter der Heizung startet in °C                       */
#define SOL_dT_ein_SW            7.0    /* Einschalt-Diff.temp. fuer Solarpumpe und Speicherabsperrventile  in °C */
#define SOL_dT_aus_SW            3.5    /* Ausschalt-Diff.temp. fuer Solarpumpe und Speicherabsperrventile  in °C */
#define SOL_KOLL_T_max         125.0    /* Max. Kollektortemperatur in °C                                         */
#define SOL_SP_T_max           110.0    /* Max. Speichertemperatur in °C                                          */
#define SOl_SP1_T_min           50.0    /* Min. Temperatur Speicher 1 in °C                                       */
#define KES_SP_dT_SW            10.0    /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in ° C            */
#define	HK_Tvl_Steigung          1.4    /* Heizkoerperheizkreis Heizkurvensteigung                                */
#define HK_Tvl_Niveau            0.0    /* Heizkoerperheizkreis Heizkurvenparallelverschiebung                    */
#define HK_Tvl_Absenk           10.0    /* Heizkoerperheizkreis Nachtabsenkung in °C                              */
#define HK_Tvl_Min              10.0    /* Heizkoerperheizkreis Frostschutztemperatur in °C                       */
#define HK_Tvl_Max              75.0    /* Heizkoerperheizkreis maximale Vorlauftemperatur in °C                  */
#define HK_Frostschutz           3.0    /* Aussentemperatur ab der Heizkreis in Betrieb ist in °C                 */
#define HK_REG_Kp               10.0    /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K                     */
#define HK_REG_Tn               15.0    /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten                */
#define HK_Tr_SW                20.5    /* Heizkoerperheizkreis Raumtemperatur Sollwert                           */
#define FB_Tvl_Steigung          0.7    /* Fussbodenheizkreis Heizkurvensteigung                                  */
#define FB_Tvl_Niveau           20.0    /* Fussbodenheizkreis Heizkurven Parallelverschiebung                     */
#define FB_Tr_SW                20.5    /* Fussbodenheizkreis Raumtemperatursollwert in °C                        */
#define FB_Tvl_Absenk           10.0    /* Fussbodenheizkreis Nachtabsenkung in °C                                */
#define FB_Tvl_Min              10.0    /* Fussbodenheizkreis Frostschutztemperatur in °C                         */
#define FB_Tvl_Max              35.0    /* Fussbodenheizkreis max. Vorlauftemperatur in °C                        */
#define FB_REG_Kp                5.0    /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K                       */
#define FB_REG_Tn               15.0    /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten                  */
#define WW_Tww_SW               40.0    /* Warmwasser-Temperatur-Sollwert in °C                                   */
#define WW_Tww_Max              60.0    /* Warmwasser-Maximaltemperatur	in °C                                     */
#define WZ_Faktor                1.0    /* Waermezaehler auf Pumpenstellbefehl                                    */
#define Wz_Max                  25.0    /* Max. Warmwasserdurchfluss in l/min                                     */
#define WW_PU_REG_Kp            20.0    /* WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp                         */
#define WW_PU_REG_Tn             0.6    /* WW-Temperatur-Regelung (Pumpe) Nachlaufzeit Tn                         */
#define WW_MV_REG_Kp            10.0    /* WW Hzg-VL-Temperatur-Regelung (Mischer) Verstaerkung Kp                */
#define WW_MV_REG_Tn            15.0    /* WW Hzg-VL-Temperatur-Regelung (Mischer) Nachlaufzeit Tn                */
#define WW_Tww_Tvl_Faktor        1.0    /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.                   */
#define WW_Tz_SW                40.0    /* Temperatursollwert des Zirkulationswassers in °C                       */
#define WW_MV_KORR               3.0    /* Korrekturfaktor fuer MV-Kennlinie                                      */

#define ABTASTZEIT_USEC     1000000L    /* das gleiche als LONG in Mikrosekunden fuer usleep Operation            */
#define ABTASTZEIT          ((float)ABTASTZEIT_USEC)/1000000L) /* Abtastzeit für digitale Regler Algorithmen      */            

#define PARSE_SET_N         36
#define VORGABENDATEI       "vorgaben.ini"

/* <Defines/> */

/* <Typen> */
typedef struct {
    char *VarName;
    void *VarPointer;
    char *format;
} parse_set_t;
/* <Typen/> */

/* <Variablen> */
#undef PUBLIC
#ifdef _PARAM_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

PUBLIC int   param_all_tau_mittel_zeit; /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)                 */
PUBLIC int   param_all_partydauer;      /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)                 */
PUBLIC float param_all_frostschutz;     /* Aussentemperatur unter der Heizkreis immer in Betrieb in ° C                    */
PUBLIC float param_all_at_start;        /* Aussentemperatur unter der Heizung startet in ° C                               */

PUBLIC float param_sol_dt_ein_sw;       /* Einschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in °C */
PUBLIC float param_sol_dt_aus_sw;       /* Ausschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in °C */
PUBLIC float param_sol_koll_t_max;      /* Max. Kollektortemperatur in °C                                                  */
PUBLIC float param_sol_sp_t_max;        /* Max. Speichertemperatur in °C                                                   */
PUBLIC float param_sol_sp1_t_min;       /* Min. Temperatur Speicher 1 in °C                                                */

PUBLIC float param_kes_sp_dt_sw;        /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in °C                      */

PUBLIC float param_hk_tvl_steigung;     /* Heizkoerperheizkreis Heizkurvensteigung                                         */
PUBLIC float param_hk_tvl_niveau;       /* Heizkoerperheizkreis Heizkurvenparallelverschiebung                             */
PUBLIC float param_hk_tvl_absenk;       /* Heizkoerperheizkreis Nachtabsenkung in °C                                       */
PUBLIC float param_hk_tvl_min;          /* Heizkoerperheizkreis Frostschutztemperatur in °C                                */
PUBLIC float param_hk_tvl_max;          /* Heizkoerperheizkreis maximale Vorlauftemperatur in °C                           */
PUBLIC float param_hk_frostschutz;      /* Aussentemperatur ab der Heizkreis in Betrieb ist in °C                          */
PUBLIC float param_hk_reg_kp;           /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K                              */
PUBLIC float param_hk_reg_tn;           /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten                         */
PUBLIC float param_hk_tr_sw;            /* Heizkoerperheizkreis Raumtemperatur Sollwert                                    */

PUBLIC float param_fb_tvl_steigung;     /* Fussbodenheizkreis Heizkurvensteigung                                           */
PUBLIC float param_fb_tvl_niveau;       /* Fussbodenheizkreis Heizkurven Parallelverschiebung                              */
PUBLIC float param_fb_tr_sw;            /* Fussbodenheizkreis Raumtemperatursollwert in °C                                 */
PUBLIC float param_fb_tvl_absenk;       /* Fussbodenheizkreis Nachtabsenkung in °C                                         */
PUBLIC float param_fb_tvl_min;          /* Fussbodenheizkreis Frostschutztemperatur in °C                                  */
PUBLIC float param_fb_tvl_max;          /* Fussbodenheizkreis max. Vorlauftemperatur in °C                                 */
PUBLIC float param_fb_reg_kp;           /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K                                */
PUBLIC float param_fb_reg_tn;           /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten                           */

PUBLIC float param_ww_tww_sw;           /* Warmwasser-Temperatur-Sollwert in °C                                            */
PUBLIC float param_ww_tww_max;          /* Warmwasser-Maximaltemperatur in °C                                              */
PUBLIC float param_wz_faktor;           /* Waermezaehler auf Pumpenstellbefehl                                             */
PUBLIC float param_wz_max;              /* Max. Warmwasserdurchfluss in l/min                                              */

PUBLIC float param_ww_pu_reg_kp;        /* WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp                                  */
PUBLIC float param_ww_pu_reg_tn;        /* WW-Temperatur-Regelung (Pumpe) Nachlaufzeit Tn                                  */
PUBLIC float param_ww_mv_korr;          /* WW Hzg-VL-Temperatur-Steurung (Mischer) Korrekturfaktor                         */

PUBLIC float param_ww_tww_tvl_faktor;   /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.                            */
PUBLIC float param_ww_tz_sw;            /* Temperatursollwert des Zirkulationswassers in °C                                */

PUBLIC int   param_hour_offset;         /* Workaround fuer localtime() Fehler                                              */
/* <Variablen/> */

/* <Konstanten> */
#ifdef _PARAM_C_
const parse_set_t Vorgaben[PARSE_SET_N] = {
    { "ALL_Tau_mittel_Zeit", &param_all_tau_mittel_zeit, "%d" }, //  0
    { "ALL_Partydauer",      &param_all_partydauer,      "%d" }, //  1
    { "ALL_Frostschutz",     &param_all_frostschutz,     "%f" }, //  2
    { "ALL_AT_Start",        &param_all_at_start,        "%f" }, //  3
    { "SOL_dT_ein_SW",       &param_sol_dt_ein_sw,       "%f" }, //  4
    { "SOL_dT_aus_SW",       &param_sol_dt_aus_sw,       "%f" }, //  5
    { "SOL_KOLL_T_max",      &param_sol_koll_t_max,      "%f" }, //  6
    { "SOL_SP_T_max",        &param_sol_sp_t_max,        "%f" }, //  7
    { "SOL_SP1_T_min",       &param_sol_sp1_t_min,       "%f" }, //  8
    { "KES_SP_dT_SW",        &param_kes_sp_dt_sw,        "%f" }, //  9
    { "HK_Tvl_Steigung",     &param_hk_tvl_steigung,     "%f" }, // 10
    { "HK_Tvl_Niveau",       &param_hk_tvl_niveau,       "%f" }, // 11
    { "HK_Tvl_Absenk",       &param_hk_tvl_absenk,       "%f" }, // 12
    { "HK_Tvl_Min",          &param_hk_tvl_min,          "%f" }, // 13
    { "HK_Tvl_Max",          &param_hk_tvl_max,          "%f" }, // 14
    { "HK_Frostschutz",      &param_hk_frostschutz,      "%f" }, // 15
    { "HK_REG_Kp",           &param_hk_reg_kp,           "%f" }, // 16
    { "HK_REG_Tn",           &param_hk_reg_tn,           "%f" }, // 17
    { "HK_Tr_SW",            &param_hk_tr_sw,            "%f" }, // 18
    { "FB_Tvl_Steigung",     &param_fb_tvl_steigung,     "%f" }, // 19
    { "FB_Tvl_Niveau",       &param_fb_tvl_niveau,       "%f" }, // 20
    { "FB_Tr_SW",            &param_fb_tr_sw,            "%f" }, // 21
    { "FB_Tvl_Absenk",       &param_fb_tvl_absenk,       "%f" }, // 22
    { "FB_Tvl_Min",          &param_fb_tvl_min,          "%f" }, // 23
    { "FB_Tvl_Max",          &param_fb_tvl_max,          "%f" }, // 24
    { "FB_REG_Kp",           &param_fb_reg_kp,           "%f" }, // 25
    { "FB_REG_Tn",           &param_fb_reg_tn,           "%f" }, // 26
    { "WW_Tww_SW",           &param_ww_tww_sw,           "%f" }, // 27
    { "WW_Tww_Max",          &param_ww_tww_max,          "%f" }, // 28
    { "WZ_Faktor",           &param_wz_faktor,           "%f" }, // 29
    { "WZ_Max",              &param_wz_max,              "%f" }, // 30
    { "WW_PU_REG_Kp",        &param_ww_pu_reg_kp,        "%f" }, // 31
    { "WW_PU_REG_Tn",        &param_ww_pu_reg_tn,        "%f" }, // 32
    { "WW_MV_KORR",          &param_ww_mv_korr,          "%f" }, // 33
    { "WW_Tww_Tvl_Faktor",   &param_ww_tww_tvl_faktor,   "%f" }, // 34
    { "WW_Tz_SW",            &param_ww_tz_sw,            "%f" }  // 35
};
#else
extern parse_set_t Vorgaben[];
#endif
/* <Konstanten/> */

/* <Prototypen> */
int param_Init( void );
/* <Prototypen/> */

#endif

