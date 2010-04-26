#ifndef VORGABE_H
#define VORGABE_H

/* Vorgabewerte: */
#define ALL_Tau_mittel_Zeit       36    /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)      */
#define MAX_ALL_Tau_mittel_Zeit   48    /* max. Wert aus Kommentar in vorgaben.ini                              */
#define ALL_Partydauer           120    /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)      */
#define ALL_Frostschutz           30    /* Aussentemperatur unter der Heizkreis immer in Betrieb	in 1/10 C   */
#define ALL_AT_Start             150    /* Aussentemperatur unter der Heizung startet in 1/10 C                 */

#define SOL_dT_ein_SW             70    /* Einschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in 1/10 C */
#define SOL_dT_aus_SW             35    /* Ausschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in 1/10 C */
#define SOL_KOLL_T_max          1250    /* Max. Kollektortemperatur in 1/10 C       */
#define SOL_SP_T_max            1100    /* Max. Speichertemperatur in 1/10 C        */
#define SOl_SP1_T_min            500    /* Min. Temperatur Speicher 1 in 1/10 C     */

#define KES_SP_dT_SW             100    /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in 1/10 C   */

#define	HK_Tvl_Steigung           1.4   /* Heizkoerperheizkreis Heizkurvensteigung                          */
#define HK_Tvl_Niveau             0.0   /* Heizkoerperheizkreis Heizkurvenparallelverschiebung              */
#define HK_Tvl_Absenk            100    /* Heizkoerperheizkreis Nachtabsenkung in 1/10 C                    */
#define HK_Tvl_Min               100    /* Heizkoerperheizkreis Frostschutztemperatur in 1/10 C             */
#define HK_Tvl_Max               750    /* Heizkoerperheizkreis maximale Vorlauftemperatur in 1/10 C        */
#define HK_Frostschutz            30    /* Aussentemperatur ab der Heizkreis in Betrieb ist in 1/10 C       */
#define HK_REG_Kp                 1.0   /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K               */
#define HK_REG_Tn                 1.0   /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten          */
#define HK_Tr_SW                 205    /* Heizkoerperheizkreis Raumtemperatur Sollwert                     */

#define FB_Tvl_Steigung           0.7   /* Fussbodenheizkreis Heizkurvensteigung                            */
#define FB_Tvl_Niveau            20.0   /* Fussbodenheizkreis Heizkurven Parallelverschiebung               */
#define FB_Tr_SW                 205    /* Fussbodenheizkreis Raumtemperatursollwert in 1/10 C              */
#define FB_Tvl_Absenk            100    /* Fussbodenheizkreis Nachtabsenkung in 1/10 C                      */
#define FB_Tvl_Min               100    /* Fussbodenheizkreis Frostschutztemperatur in 1/10 C               */
#define FB_Tvl_Max               350    /* Fussbodenheizkreis max. Vorlauftemperatur in 1/10 C              */

#define FB_REG_Kp                 1.0   /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K                 */
#define FB_REG_Tn                 1.0   /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten            */

#define WW_Tww_SW                400    /* Warmwasser-Temperatur-Sollwert in 1/10 C                         */
#define WW_Tww_Max               600    /* Warmwasser-Maximaltemperatur	in 1/10                             */
#define WZ_Faktor                 1.0   /* Waermezaehler auf Pumpenstellbefehl                              */
#define Wz_Max                   25.0   /* Max. Warmwasserdurchfluss in l/min                               */
#define WW_HZG_REG_Kp             1.0   /* Heizungs-VL-Temperatur-Regelung Verstaerkung Kp                  */
#define WW_HZG_REG_Tn             1.0   /* Heizungs-VL-Temperatur-Regelung Nachlaufzeit Tn                  */
#define WW_Tww_Tvl_Faktor         1.0   /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.             */
#define WW_Tz_SW                 400    /* Temperatursollwert des Zirkulationswassers in 1/10 C             */

/* Variablendefinitionen fuer Vorgabe Variablen, initialisiert in init_variables() */

#undef _EXT_
#ifdef _MAIN_C_
    #define _EXT_ 
#else
    #define _EXT_ extern
#endif

_EXT_ int all_tau_mittel_zeit;      /* Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)    */
_EXT_ int all_partydauer;           /* Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)    */
_EXT_ int all_frostschutz;          /* Aussentemperatur unter der Heizkreis immer in Betrieb in 1/10 C    */
_EXT_ int all_at_start;             /* Aussentemperatur unter der Heizung startet in 1/10 C              */

_EXT_ int sol_dt_ein_sw;            /* Einschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in 1/10 �C */
_EXT_ int sol_dt_aus_sw;            /* Ausschalt-Differenztemperatur fuer Solarpumpe und Speicherabsperrventile  in 1/10 �C */
_EXT_ int sol_koll_t_max;           /* Max. Kollektortemperatur in 1/10 C       */
_EXT_ int sol_sp_t_max;             /* Max. Speichertemperatur in 1/10 C        */
_EXT_ int sol_sp1_t_min;            /* Min. Temperatur Speicher 1 in 1/10 C     */

_EXT_ int kes_sp_dt_sw;             /* Temperaturdifferenz zwischen Kessel- und Speicher-SW in 1/10 C */

_EXT_ float hk_tvl_steigung;        /* Heizkoerperheizkreis Heizkurvensteigung                      */
_EXT_ float hk_tvl_niveau;          /* Heizkoerperheizkreis Heizkurvenparallelverschiebung          */
_EXT_ int hk_tvl_absenk;            /* Heizkoerperheizkreis Nachtabsenkung in 1/10 C                */
_EXT_ int hk_tvl_min;               /* Heizkoerperheizkreis Frostschutztemperatur in 1/10 C         */
_EXT_ int hk_tvl_max;               /* Heizkoerperheizkreis maximale Vorlauftemperatur in 1/10 C    */
_EXT_ int hk_frostschutz;           /* Aussentemperatur ab der Heizkreis in Betrieb ist in 1/10 C   */
_EXT_ float hk_reg_kp;              /* Heizkoerperheizkreis Verstaerkung PI-Regler in %/K           */
_EXT_ float hk_reg_tn;              /* Heizkoerperheizkreis Nachstellzeit PI-Regler in Minuten      */
_EXT_ int hk_tr_sw;                 /* Heizkoerperheizkreis Raumtemperatur Sollwert                 */

_EXT_ float fb_tvl_steigung;        /* Fussbodenheizkreis Heizkurvensteigung                        */
_EXT_ float fb_tvl_niveau;          /* Fussbodenheizkreis Heizkurven Parallelverschiebung           */
_EXT_ int fb_tr_sw;                 /* Fussbodenheizkreis Raumtemperatursollwert in 1/10 C          */
_EXT_ int fb_tvl_absenk;            /* Fussbodenheizkreis Nachtabsenkung in 1/10 C                  */
_EXT_ int fb_tvl_min;               /* Fussbodenheizkreis Frostschutztemperatur in 1/10 C           */
_EXT_ int fb_tvl_max;               /* Fussbodenheizkreis max. Vorlauftemperatur in 1/10 C          */

_EXT_ float fb_reg_kp;              /* Fussbodenheizkreis Verstaerkung PI-Regler in %/K             */
_EXT_ float fb_reg_tn;              /* Fussbodenheizkreis Nachstellzeit PI-Regler in Minuten        */

_EXT_ int ww_tww_sw;                /* Warmwasser-Temperatur-Sollwert in 1/10 C                 */
_EXT_ int ww_tww_max;               /* Warmwasser-Maximaltemperatur	in 1/10 C                   */
_EXT_ float wz_faktor;              /* Waermezaehler auf Pumpenstellbefehl                      */
_EXT_ float wz_max;                 /* Max. Warmwasserdurchfluss in l/min                       */

_EXT_ float ww_hzg_reg_kp;          /* Heizungs-VL-Temperatur-Regelung Verstaerkung Kp          */
_EXT_ float ww_hzg_reg_tn;          /* Heizungs-VL-Temperatur-Regelung Nachlaufzeit Tn          */
_EXT_ float ww_tww_tvl_faktor;      /* Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.     */
_EXT_ int ww_tz_sw;                 /* Temperatursollwert des Zirkulationswassers in 1/10 C     */

#endif


