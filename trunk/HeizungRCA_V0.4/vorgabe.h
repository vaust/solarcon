#ifndef VORGABE_H
#define VORGABE_H

/* Vorgabewerte: */
#define ALL_Tau_mittel_Zeit       36    /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)      */
#define MAX_ALL_Tau_mittel_Zeit   48    /* max. Wert aus Kommentar in vorgaben.ini                              */
#define ALL_Partydauer           120    /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)      */
#define ALL_Frostschutz          3.0    /* Aussentemperatur unter der Heizkreis immer in Betrieb in °C   */
#define ALL_AT_Start            15.0    /* Aussentemperatur unter der Heizung startet in °C            */

#define SOL_dT_ein_SW            7.0    /* Einschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in °C */
#define SOL_dT_aus_SW            3.5    /* Ausschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in °C */
#define SOL_KOLL_T_max         125.0    /* Max. Kollektortemperatur in °C       */
#define SOL_SP_T_max           110.0    /* Max. Speichertemperatur in °C        */
#define SOl_SP1_T_min           50.0    /* Min. Temperatur Speicher 1 in °C     */

#define KES_SP_dT_SW            10.0    /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in ° C   */

#define	HK_Tvl_Steigung          1.4    /* Heizkoerperheizkreis Heizkurvensteigung                          */
#define HK_Tvl_Niveau            0.0    /* Heizkoerperheizkreis Heizkurvenparallelverschiebung              */
#define HK_Tvl_Absenk           10.0    /* Heizkoerperheizkreis Nachtabsenkung in °C                */
#define HK_Tvl_Min              10.0    /* Heizkoerperheizkreis Frostschutztemperatur in °C         */
#define HK_Tvl_Max              75.0    /* Heizkoerperheizkreis maximale Vorlauftemperatur in °C    */
#define HK_Frostschutz           3.0    /* Aussentemperatur ab der Heizkreis in Betrieb ist in °C   */
#define HK_REG_Kp               10.0    /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K       */
#define HK_REG_Tn               15.0    /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten  */
#define HK_Tr_SW                20.5    /* Heizkoerperheizkreis Raumtemperatur Sollwert             */

#define FB_Tvl_Steigung          0.7    /* Fussbodenheizkreis Heizkurvensteigung                            */
#define FB_Tvl_Niveau           20.0    /* Fussbodenheizkreis Heizkurven Parallelverschiebung               */
#define FB_Tr_SW                20.5    /* Fussbodenheizkreis Raumtemperatursollwert in °C              */
#define FB_Tvl_Absenk           10.0    /* Fussbodenheizkreis Nachtabsenkung in °C                      */
#define FB_Tvl_Min              10.0    /* Fussbodenheizkreis Frostschutztemperatur in °C               */
#define FB_Tvl_Max              35.0    /* Fussbodenheizkreis max. Vorlauftemperatur in °C              */

#define FB_REG_Kp                5.0    /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K                 */
#define FB_REG_Tn               15.0    /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten            */

#define WW_Tww_SW               40.0    /* Warmwasser-Temperatur-Sollwert in °C                         */
#define WW_Tww_Max              60.0    /* Warmwasser-Maximaltemperatur	in °C                           */
#define WZ_Faktor                1.0    /* Waermezaehler auf Pumpenstellbefehl                          */
#define Wz_Max                  25.0    /* Max. Warmwasserdurchfluss in l/min                           */
#define WW_PU_REG_Kp            20.0    /* WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp              */
#define WW_PU_REG_Tn            0.6     /* WW-Temperatur-Regelung (Pumpe) Nachlaufzeit Tn              */
#define WW_MV_REG_Kp            10.0    /* WW Hzg-VL-Temperatur-Regelung (Mischer) Verstaerkung Kp              */
#define WW_MV_REG_Tn            15.0    /* WW Hzg-VL-Temperatur-Regelung (Mischer) Nachlaufzeit Tn              */

#define WW_Tww_Tvl_Faktor        1.0    /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.         */
#define WW_Tz_SW                40.0    /* Temperatursollwert des Zirkulationswassers in °C             */

/* Variablendefinitionen fuer Vorgabe Variablen, initialisiert in init_variables() */

#undef _EXT_
#ifdef _MAIN_C_
    #define _EXT_
#else
    #define _EXT_ extern
#endif

_EXT_ int all_tau_mittel_zeit;   /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)    */
_EXT_ int all_partydauer;        /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)    */
_EXT_ float all_frostschutz;     /* Aussentemperatur unter der Heizkreis immer in Betrieb in ° C    */
_EXT_ float all_at_start;        /* Aussentemperatur unter der Heizung startet in ° C              */

_EXT_ float sol_dt_ein_sw;       /* Einschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in ° �C */
_EXT_ float sol_dt_aus_sw;       /* Ausschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in ° �C */
_EXT_ float sol_koll_t_max;      /* Max. Kollektortemperatur in °C       */
_EXT_ float sol_sp_t_max;        /* Max. Speichertemperatur in °C        */
_EXT_ float sol_sp1_t_min;       /* Min. Temperatur Speicher 1 in °C     */

_EXT_ float kes_sp_dt_sw;        /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in °C  */

_EXT_ float hk_tvl_steigung;     /* Heizkoerperheizkreis Heizkurvensteigung                      */
_EXT_ float hk_tvl_niveau;       /* Heizkoerperheizkreis Heizkurvenparallelverschiebung          */
_EXT_ float hk_tvl_absenk;       /* Heizkoerperheizkreis Nachtabsenkung in °C                */
_EXT_ float hk_tvl_min;          /* Heizkoerperheizkreis Frostschutztemperatur in °C         */
_EXT_ float hk_tvl_max;          /* Heizkoerperheizkreis maximale Vorlauftemperatur in °C    */
_EXT_ float hk_frostschutz;      /* Aussentemperatur ab der Heizkreis in Betrieb ist in °C   */
_EXT_ float hk_reg_kp;           /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K           */
_EXT_ float hk_reg_tn;           /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten      */
_EXT_ float hk_tr_sw;            /* Heizkoerperheizkreis Raumtemperatur Sollwert                 */

_EXT_ float fb_tvl_steigung;     /* Fussbodenheizkreis Heizkurvensteigung                        */
_EXT_ float fb_tvl_niveau;       /* Fussbodenheizkreis Heizkurven Parallelverschiebung           */
_EXT_ float fb_tr_sw;            /* Fussbodenheizkreis Raumtemperatursollwert in °C          */
_EXT_ float fb_tvl_absenk;       /* Fussbodenheizkreis Nachtabsenkung in °C                  */
_EXT_ float fb_tvl_min;          /* Fussbodenheizkreis Frostschutztemperatur in °C           */
_EXT_ float fb_tvl_max;          /* Fussbodenheizkreis max. Vorlauftemperatur in °C          */
_EXT_ float fb_reg_kp;           /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K             */
_EXT_ float fb_reg_tn;           /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten        */

_EXT_ float ww_tww_sw;           /* Warmwasser-Temperatur-Sollwert in °C                     */
_EXT_ float ww_tww_max;          /* Warmwasser-Maximaltemperatur	in °C                    */
_EXT_ float wz_faktor;           /* Waermezaehler auf Pumpenstellbefehl                      */
_EXT_ float wz_max;              /* Max. Warmwasserdurchfluss in l/min                       */

_EXT_ float ww_pu_reg_kp;        /* WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp              */
_EXT_ float ww_pu_reg_tn;        /* WW-Temperatur-Regelung (Pumpe) Nachlaufzeit Tn              */
_EXT_ float ww_mv_reg_kp;        /* WW Hzg-VL-Temperatur-Regelung (Mischer) Verstaerkung Kp              */
_EXT_ float ww_mv_reg_tn;        /* WW Hzg-VL-Temperatur-Regelung (Mischer) Nachlaufzeit Tn              */

_EXT_ float ww_tww_tvl_faktor;   /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.     */
_EXT_ float ww_tz_sw;            /* Temperatursollwert des Zirkulationswassers in °C         */

_EXT_ int   hour_offset;         /* Workaround fuer localtime() Fehler */

#endif


