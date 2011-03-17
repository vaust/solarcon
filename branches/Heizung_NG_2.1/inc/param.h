#ifndef _PARAM_H_
#define _PARAM_H_

#include "gen_types.h"

/* <Defines> */
/* Vorgabewerte: */
#ifdef _PARAM_C_
#define ALL_Tau_mittel_Zeit    36    /**< Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)            */
#define ALL_Partydauer        120    /**< Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)            */
#define ALL_Frostschutz       3.0    /**< Aussentemperatur unter der Heizkreis immer in Betrieb in Grad C            */
#define ALL_AT_Start         15.0    /**< Aussentemperatur unter der Heizung startet in Grad C                       */
#define SOL_dT_ein_SW         7.0    /**< Einschalt-Diff.temp. fuer Solarpumpe und Speicherabsperrventile  in Grad C */
#define SOL_dT_aus_SW         3.5    /**< Ausschalt-Diff.temp. fuer Solarpumpe und Speicherabsperrventile  in Grad C */
#define SOL_KOLL_T_max      125.0    /**< Max. Kollektortemperatur in Grad C                                         */
#define SOL_SP_T_max        110.0    /**< Max. Speichertemperatur in Grad C                                          */
#define SOl_SP1_T_min        50.0    /**< Min. Temperatur Speicher 1 in Grad C                                       */
#define KES_SP_dT_SW         10.0    /**< Temperaturdifferenz zwischen Kessel- und Speicher-SW in Grad C             */
#define	HK_Tvl_Steigung       1.4    /**< Heizkoerperheizkreis Heizkurvensteigung                                    */
#define HK_Tvl_Niveau         0.0    /**< Heizkoerperheizkreis Heizkurvenparallelverschiebung                        */
#define HK_Tvl_Absenk        10.0    /**< Heizkoerperheizkreis Nachtabsenkung in Grad C                              */
#define HK_Tvl_Min           10.0    /**< Heizkoerperheizkreis Frostschutztemperatur in Grad C                       */
#define HK_Tvl_Max           75.0    /**< Heizkoerperheizkreis maximale Vorlauftemperatur in Grad C                  */
#define HK_Frostschutz        3.0    /**< Aussentemperatur ab der Heizkreis in Betrieb ist in Grad C                 */
#define HK_REG_Kp            10.0    /**< Heizkoerperheizkreis Verstaerkung PI-Regler in %/K                         */
#define HK_REG_Ki             0.067  /**< Heizkoerperheizkreis Verstaerkung I-Anteil PI-Regler in %/(K x s)          */
#define HK_REG_AP            50.0    /**< Heizkoerperheizkreis Arbeitspunktoffset in %                               */
#define HK_Tr_SW             20.5    /**< Heizkoerperheizkreis Raumtemperatur Sollwert                               */
#define FB_Tvl_Steigung       0.7    /**< Fussbodenheizkreis Heizkurvensteigung                                      */
#define FB_Tvl_Niveau        20.0    /**< Fussbodenheizkreis Heizkurven Parallelverschiebung                         */
#define FB_Tr_SW             20.5    /**< Fussbodenheizkreis Raumtemperatursollwert in Grad C                        */
#define FB_Tvl_Absenk        10.0    /**< Fussbodenheizkreis Nachtabsenkung in Grad C                                */
#define FB_Tvl_Min           10.0    /**< Fussbodenheizkreis Frostschutztemperatur in Grad C                         */
#define FB_Tvl_Max           35.0    /**< Fussbodenheizkreis max. Vorlauftemperatur in Grad C                        */
#define FB_REG_Kp             5.0    /**< Fussbodenheizkreis Verstaerkung PI-Regler in %/K                           */
#define FB_REG_Ki             0.2    /**< Fussbodenheizkreis Verstaerkung I-Anteil PI-Regler in %/(K x s)            */
#define FB_REG_AP            50.0    /**< Fussbodenheizkreis Arbeitspunktoffset in %                                 */
#define WW_Tww_SW            40.0    /**< Warmwasser-Temperatur-Sollwert in Grad C                                   */
#define WW_Tww_Max           60.0    /**< Warmwasser-Maximaltemperatur	in Grad C                                     */
#define WZ_Faktor             1.0    /**< Waermezaehler auf Pumpenstellbefehl                                        */
#define Wz_Max               25.0    /**< Max. Warmwasserdurchfluss in l/min                                         */
#define WW_PU_REG_Kp         20.0    /**< WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp                             */
#define WW_PU_REG_Ki          0.05   /**< WW-Temperatur-Regelung (Pumpe) Verstaerkung I-Anteil PI-Regler in %/(K x s)*/
#define WW_PU_REG_AP         50.0    /**< WW-Temperatur-Regelung (Pumpe) Arbeitspunktoffset in %                     */
#define WW_MV_REG_Kp         10.0    /**< WW Hzg-VL-Temperatur-Regelung (Mischer) Verstaerkung Kp                    */
#define WW_MV_REG_Ki          0.1    /**< WW Hzg-VL-Temperatur-Regelung (Mischer) Verstaerkung Ki in %/(K x s)       */
#define WW_MV_REG_AP         50.0    /**< WW Hzg-VL-Temperatur-Regelung (Mischer) Arbeitspunktoffset in %            */
#define WW_Tww_Tvl_Faktor     1.0    /**< Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.                       */
#define WW_Tz_SW             40.0    /**< Temperatursollwert des Zirkulationswassers in Grad C                       */
#define WW_MV_KORR            3.0    /**< Korrekturfaktor fuer MV-Kennlinie                                          */

#ifdef __WAGO__
    #define VORGABENDATEI           "/home/vorgaben7.ini"
#else
    #define VORGABENDATEI           "vorgaben7.ini"
#endif

#endif /* _PARAM_C_ */

#define MAX_ALL_Tau_mittel_Zeit   48                /**< max. Wert aus Kommentar in vorgaben.ini                     */

#define USEC2SEC(x)     (((float)(x))/1.0e6)        /**< usec in sekunden umrechnen                                  */
#define USEC2MSEC(x)    ((x)/1000)                  /**< usec in msec umrechnen                                      */
#define ABTASTZEIT_USEC 500000L                     /**< das gleiche als LONG in Mikrosekunden fuer Timerlaufzeit    */
#define ABTASTZEIT      USEC2SEC(ABTASTZEIT_USEC)   /**< Abtastzeit fuer digitale Regler Algorithmen als float       */


/* <Defines/> */

/* <Typen> */
typedef struct parse_set_s {
    char *VarName;
    void *VarPointer;
    char *format;
    // char *einheit;
} parse_set_t;

typedef struct param_all_s {
    int   tau_mittel_zeit; /**< Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)           */
    int   partydauer;      /**< Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)           */
    float frostschutz;     /**< Aussentemperatur unter der Heizkreis immer in Betrieb in Grad C           */
    float at_start;        /**< Aussentemperatur unter der Heizung startet in Grad C                      */
} param_all_t;

typedef struct param_sol_s {
    float dt_ein_sw;       /**< Einschalt-Differenztemp. fuer Solarpumpe und Speicherabsperrv. in Grad C  */
    float dt_aus_sw;       /**< Ausschalt-Differenztemp. fuer Solarpumpe und Speicherabsperrv. in Grad C  */
    float koll_t_max;      /**< Max. Kollektortemperatur in Grad C                                        */
    float sp_t_max;        /**< Max. Speichertemperatur in Grad C                                         */
    float sp1_t_min;       /**< Min. Temperatur Speicher 1 in Grad C                                      */
} param_sol_t;

typedef struct param_kes_s {
    float sp_dt_sw;        /**< Temperaturdifferenz zwischen Kessel- und Speicher-SW in Grad C            */
} param_kes_t;

typedef struct param_tvl_s {
    float steigung;         /**< Heizkreis Heizkurvensteigung                                             */
    float niveau;           /**< Heizkreis Heizkurvenparallelverschiebung                                 */
    float absenk;           /**< Heizkreis Nachtabsenkung in Grad C                                       */
    float min;              /**< Heizkreis Frostschutztemperatur in Grad C                                */
    float max;              /**< Heizkreis maximale Vorlauftemperatur in Grad C                           */
} param_tvl_t;

typedef struct param_reg_s {
    float kp;               /**< Regler Verstaerkung PI-Regler in %/K                                     */
    float ki;               /**< Regler Verstaerkung PI-Regler I-Anteil in %/(K x s)                      */
    float ap;               /**< Regler Arbeitspunktoffset in %                                           */
} param_reg_t;

typedef struct param_hk_s {
    param_tvl_t tvl;
    param_reg_t reg;
    float       frostschutz;      /**< Aussentemperatur ab der Heizkreis in Betrieb ist in Grad C         */
    float       tr_sw;            /**< Heizkoerperheizkreis Raumtemperatur Sollwert                       */
} param_hk_t;

typedef struct param_fb_s {
    param_tvl_t tvl;
    param_reg_t reg;
    float tr_sw;                /**< Fussbodenheizkreis Raumtemperatursollwert in Grad C                  */
} param_fb_t;

typedef struct param_ww_s {
    float tww_sw;           /**< Warmwasser-Temperatur-Sollwert in Grad C                              */
    float tww_max;          /**< Warmwasser-Maximaltemperatur in Grad C                                */
    float wz_faktor;        /**< Waermezaehler auf Pumpenstellbefehl                                   */
    float wz_max;           /**< Max. Warmwasserdurchfluss in l/min                                    */
    param_reg_t pu_reg;     /**< WW-Temperatur-Regler                                                  */
    float mv_korr;          /**< WW Hzg-VL-Temperatur-Steurung (Mischer) Korrekturfaktor               */
    float tww_tvl_faktor;   /**< Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.                  */
    float tz_sw;            /**< Temperatursollwert des Zirkulationswassers in Grad C                  */
} param_ww_t;

typedef struct param_sys_s {
    u32_t zykluszeit;          /**< Zykluszeit des Systems in Mikrosekunden                               */
} param_sys_t;

/**
 * @brief Zusammenfassung aller Parameter in einer Struktur
 */
typedef struct param_satz_s {
    param_all_t all;
    param_sol_t sol;
    param_kes_t kes;
    param_hk_t  hk;
    param_fb_t  fb;
    param_ww_t  ww;
    param_sys_t sys;
} param_satz_t;

/* <Typen/> */

/* <Variablen> */
#undef PUBLIC
#ifdef _PARAM_C_
    #define PUBLIC
#else
    #define PUBLIC extern const
#endif

/**
 * @brief Instanz aller Parameter, die in der Struktur \ref param_satz_s definiert sind.
 */
PUBLIC param_satz_t param;
/* <Variablen/> */

/* <Konstanten> */
#ifdef _PARAM_C_
const parse_set_t param_Vorgaben[] = {
    { "ALL_Tau_mittel_Zeit", &(param.all.tau_mittel_zeit), "%d" },
    { "ALL_Partydauer",      &(param.all.partydauer),      "%d" },
    { "ALL_Frostschutz",     &(param.all.frostschutz),     "%f" },
    { "ALL_AT_Start",        &(param.all.at_start),        "%f" },
    { "SOL_dT_ein_SW",       &(param.sol.dt_ein_sw),       "%f" },
    { "SOL_dT_aus_SW",       &(param.sol.dt_aus_sw),       "%f" },
    { "SOL_KOLL_T_max",      &(param.sol.koll_t_max),      "%f" },
    { "SOL_SP_T_max",        &(param.sol.sp_t_max),        "%f" },
    { "SOL_SP1_T_min",       &(param.sol.sp1_t_min),       "%f" },
    { "KES_SP_dT_SW",        &(param.kes_sp_dt_sw),        "%f" },
    { "HK_Tvl_Steigung",     &(param.hk.tvl.steigung),     "%f" },
    { "HK_Tvl_Niveau",       &(param.hk.tvl.niveau),       "%f" },
    { "HK_Tvl_Absenk",       &(param.hk.tvl.absenk),       "%f" },
    { "HK_Tvl_Min",          &(param.hk.tvl.min),          "%f" },
    { "HK_Tvl_Max",          &(param.hk.tvl.max),          "%f" },
    { "HK_Frostschutz",      &(param.hk.frostschutz),      "%f" },
    { "HK_REG_Kp",           &(param.hk.reg.kp),           "%f" },
    { "HK_REG_Ki",           &(param.hk.reg.ki),           "%f" },
    { "HK_REG_AP",           &(param.hk.reg.ap),           "%f" },
    { "HK_Tr_SW",            &(param.hk.tr_sw),            "%f" },
    { "FB_Tvl_Steigung",     &(param.fb.tvl.steigung),     "%f" },
    { "FB_Tvl_Niveau",       &(param.fb.tvl.niveau),       "%f" },
    { "FB_Tvl_Absenk",       &(param.fb.tvl.absenk),       "%f" },
    { "FB_Tvl_Min",          &(param.fb.tvl.min),          "%f" },
    { "FB_Tvl_Max",          &(param.fb.tvl.max),          "%f" },
    { "FB_REG_Kp",           &(param.fb.reg.kp),           "%f" },
    { "FB_REG_Ki",           &(param.fb.reg.ki),           "%f" },
    { "FB_REG_AP",           &(param.fb.reg.ap),           "%f" },
    { "FB_Tr_SW",            &(param.fb.tr_sw),            "%f" },
    { "WW_Tww_SW",           &(param.ww.tww_sw),           "%f" },
    { "WW_Tww_Max",          &(param.ww.tww_max),          "%f" },
    { "WZ_Faktor",           &(param.wz.faktor),           "%f" },
    { "WZ_Max",              &(param.ww.wz_max),           "%f" },
    { "WW_PU_REG_Kp",        &(param.ww.pu_reg.kp),        "%f" },
    { "WW_PU_REG_Ki",        &(param.ww.pu_reg.ki),        "%f" },
    { "WW_PU_REG_AP",        &(param.ww.pu_reg.ap),        "%f" },
    { "WW_MV_KORR",          &(param.ww.mv_korr),          "%f" },
    { "WW_Tww_Tvl_Faktor",   &(param.ww.tww_tvl_faktor),   "%f" },
    { "WW_Tz_SW",            &(param.ww.tz_sw),            "%f" },
    { "SYS_Zykluszeit",      &(param.sys.zykluszeit),      "%d" },
    
};
const int param_Vorgaben_len = sizeof(param_Vorgaben)/sizeof(parse_set_t);

#else
extern const parse_set_t param_Vorgaben[];
extern const int param_Vorgaben_len;
#endif
/* <Konstanten/> */

/* <Prototypen> */
int param_Init( void );
#ifdef __TEST__
void param_TEST_Vorgaben( void );
#endif /* __TEST__  */
/* <Prototypen/> */

#endif

