/*
 *  SOLARCON Modular Solar Supported Home Heating Controller
 *  Copyright (C) 2011  Volker Stegmann
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    #define VORGABENDATEI   "/home/vorgaben.ini"
#else
    #define VORGABENDATEI   "vorgaben.ini"
#endif

#endif /* _PARAM_C_ */

#define MAX_ALL_Tau_mittel_Zeit   48                /**< max. Wert aus Kommentar in vorgaben.ini                      */

#define MSEC2SEC(x)     (((float)(x))/1000.0)       /**< msec in sekunden umrechnen                                   */
#define ABTASTZEIT_MSEC 1000L                       /**< Abtastzeit in Millisekunden als LONG fuer Timerlaufzeit      */
#define ABTASTZEIT      MSEC2SEC(ABTASTZEIT_MSEC)   /**< Abtastzeit fuer digitale Regler Algorithmen als float in sec */

/* <Defines/> */

/* <Typen> */

/**
 * @brief Datenstruktur zur Ausgabe von beliebigen Variablen ueber Telnet Interface
 */
typedef struct parse_set_s {
    char *VarName;
    void *VarPointer;
    char *format;
    // char *einheit;
} parse_set_t;
/* <Typen/> */

/* <Variablen> */
#undef PUBLIC
#ifdef _PARAM_C_
    #define PUBLIC
#else
    #define PUBLIC extern // const
#endif

PUBLIC int   param_all_tau_mittel_zeit; /**< Zeit ueber die die Aussentemperatur gemittelt wird (in Stunden)           */
PUBLIC int   param_all_partydauer;      /**< Fussbodenheizkreis Dauer der Betriebsverlaengerung (in Minuten)           */
PUBLIC float param_all_frostschutz;     /**< Aussentemperatur unter der Heizkreis immer in Betrieb in Grad C           */
PUBLIC float param_all_at_start;        /**< Aussentemperatur unter der Heizung startet in Grad C                      */
                                                                                                                      
PUBLIC float param_sol_dt_ein_sw;       /**< Einschalt-Differenztemp. fuer Solarpumpe und Speicherabsperrv. in Grad C  */
PUBLIC float param_sol_dt_aus_sw;       /**< Ausschalt-Differenztemp. fuer Solarpumpe und Speicherabsperrv. in Grad C  */
PUBLIC float param_sol_koll_t_max;      /**< Max. Kollektortemperatur in Grad C                                        */
PUBLIC float param_sol_sp_t_max;        /**< Max. Speichertemperatur in Grad C                                         */
PUBLIC float param_sol_sp1_t_min;       /**< Min. Temperatur Speicher 1 in Grad C                                      */
                                                                                                                       
PUBLIC float param_kes_sp_dt_sw;        /**< Temperaturdifferenz zwischen Kessel- und Speicher-SW in Grad C            */
                                                                                                                       
PUBLIC float param_hk_tvl_steigung;     /**< Heizkoerperheizkreis Heizkurvensteigung                                   */
PUBLIC float param_hk_tvl_niveau;       /**< Heizkoerperheizkreis Heizkurvenparallelverschiebung                       */
PUBLIC float param_hk_tvl_absenk;       /**< Heizkoerperheizkreis Nachtabsenkung in Grad C                             */
PUBLIC float param_hk_tvl_min;          /**< Heizkoerperheizkreis Frostschutztemperatur in Grad C                      */
PUBLIC float param_hk_tvl_max;          /**< Heizkoerperheizkreis maximale Vorlauftemperatur in Grad C                 */
PUBLIC float param_hk_frostschutz;      /**< Aussentemperatur ab der Heizkreis in Betrieb ist in Grad C                */
PUBLIC float param_hk_reg_kp;           /**< Heizkoerperheizkreis Verstaerkung PI-Regler in %/K                        */
PUBLIC float param_hk_reg_ki;           /**< Heizkoerperheizkreis Verstaerkung PI-Regler I-Anteil in %/(K x s)         */
PUBLIC float param_hk_reg_ap;           /**< Heizkoerperheizkreis Arbeitspunktoffset in %                              */
PUBLIC float param_hk_tr_sw;            /**< Heizkoerperheizkreis Raumtemperatur Sollwert                              */
                                                                                                                       
PUBLIC float param_fb_tvl_steigung;     /**< Fussbodenheizkreis Heizkurvensteigung                                     */
PUBLIC float param_fb_tvl_niveau;       /**< Fussbodenheizkreis Heizkurven Parallelverschiebung                        */
PUBLIC float param_fb_tr_sw;            /**< Fussbodenheizkreis Raumtemperatursollwert in Grad C                       */
PUBLIC float param_fb_tvl_absenk;       /**< Fussbodenheizkreis Nachtabsenkung in Grad C                               */
PUBLIC float param_fb_tvl_min;          /**< Fussbodenheizkreis Frostschutztemperatur in Grad C                        */
PUBLIC float param_fb_tvl_max;          /**< Fussbodenheizkreis max. Vorlauftemperatur in Grad C                       */
PUBLIC float param_fb_reg_kp;           /**< Fussbodenheizkreis Verstaerkung PI-Regler in %/K                          */
PUBLIC float param_fb_reg_ki;           /**< Fussbodenheizkreis Verstaerkung PI-Regler I-Anteil in %/(K x s)           */
PUBLIC float param_fb_reg_ap;           /**< Fussbodenheizkreis Arbeitspunktoffset in %                                */
                                                                                                                       
PUBLIC float param_ww_tww_sw;           /**< Warmwasser-Temperatur-Sollwert in Grad C                                  */
PUBLIC float param_ww_tww_max;          /**< Warmwasser-Maximaltemperatur in Grad C                                    */
PUBLIC float param_wz_faktor;           /**< Waermezaehler auf Pumpenstellbefehl                                       */
PUBLIC float param_wz_max;              /**< Max. Warmwasserdurchfluss in l/min                                        */
PUBLIC float param_ww_pu_reg_kp;        /**< WW-Temperatur-Regelung (Pumpe) Verstaerkung Kp                            */
PUBLIC float param_ww_pu_reg_ki;        /**< WW-Temperatur-Regelung (Pumpe) Verstaerkung Ki in %/(K x s)               */
PUBLIC float param_ww_pu_reg_ap;        /**< WW-Temperatur-Regelung (Pumpe) Arbeitspunktoffset in %                    */
PUBLIC float param_ww_mv_korr;          /**< WW Hzg-VL-Temperatur-Steurung (Mischer) Korrekturfaktor                   */
                                                                                                                       
PUBLIC float param_ww_tww_tvl_faktor;   /**< Einfluss der WW-Temperatur auf die Heizungs-VL-Temp.                      */
PUBLIC float param_ww_tz_sw;            /**< Temperatursollwert des Zirkulationswassers in Grad C                      */

PUBLIC u32_t param_sys_zykluszeit;      /**< Zykluszeit des Systems in Millisekunden                                   */
/* <Variablen/> */

/* <Konstanten> */
#ifdef _PARAM_C_
const parse_set_t param_Vorgaben[] = {
    { "ALL_Tau_mittel_Zeit", &param_all_tau_mittel_zeit, "%d" },
    { "ALL_Partydauer",      &param_all_partydauer,      "%d" },
    { "ALL_Frostschutz",     &param_all_frostschutz,     "%f" },
    { "ALL_AT_Start",        &param_all_at_start,        "%f" },
    { "SOL_dT_ein_SW",       &param_sol_dt_ein_sw,       "%f" },
    { "SOL_dT_aus_SW",       &param_sol_dt_aus_sw,       "%f" },
    { "SOL_KOLL_T_max",      &param_sol_koll_t_max,      "%f" },
    { "SOL_SP_T_max",        &param_sol_sp_t_max,        "%f" },
    { "SOL_SP1_T_min",       &param_sol_sp1_t_min,       "%f" },
    { "KES_SP_dT_SW",        &param_kes_sp_dt_sw,        "%f" },
    { "HK_Tvl_Steigung",     &param_hk_tvl_steigung,     "%f" },
    { "HK_Tvl_Niveau",       &param_hk_tvl_niveau,       "%f" },
    { "HK_Tvl_Absenk",       &param_hk_tvl_absenk,       "%f" },
    { "HK_Tvl_Min",          &param_hk_tvl_min,          "%f" },
    { "HK_Tvl_Max",          &param_hk_tvl_max,          "%f" },
    { "HK_Frostschutz",      &param_hk_frostschutz,      "%f" },
    { "HK_REG_Kp",           &param_hk_reg_kp,           "%f" },
    { "HK_REG_Ki",           &param_hk_reg_ki,           "%f" },
    { "HK_REG_AP",           &param_hk_reg_ap,           "%f" },
    { "HK_Tr_SW",            &param_hk_tr_sw,            "%f" },
    { "FB_Tvl_Steigung",     &param_fb_tvl_steigung,     "%f" },
    { "FB_Tvl_Niveau",       &param_fb_tvl_niveau,       "%f" },
    { "FB_Tr_SW",            &param_fb_tr_sw,            "%f" },
    { "FB_Tvl_Absenk",       &param_fb_tvl_absenk,       "%f" },
    { "FB_Tvl_Min",          &param_fb_tvl_min,          "%f" },
    { "FB_Tvl_Max",          &param_fb_tvl_max,          "%f" },
    { "FB_REG_Kp",           &param_fb_reg_kp,           "%f" },
    { "FB_REG_Ki",           &param_fb_reg_ki,           "%f" },
    { "FB_REG_AP",           &param_fb_reg_ap,           "%f" },
    { "WW_Tww_SW",           &param_ww_tww_sw,           "%f" },
    { "WW_Tww_Max",          &param_ww_tww_max,          "%f" },
    { "WZ_Faktor",           &param_wz_faktor,           "%f" },
    { "WZ_Max",              &param_wz_max,              "%f" },
    { "WW_PU_REG_Kp",        &param_ww_pu_reg_kp,        "%f" },
    { "WW_PU_REG_Ki",        &param_ww_pu_reg_ki,        "%f" },
    { "WW_PU_REG_AP",        &param_ww_pu_reg_ap,        "%f" },
    { "WW_MV_KORR",          &param_ww_mv_korr,          "%f" },
    { "WW_Tww_Tvl_Faktor",   &param_ww_tww_tvl_faktor,   "%f" },
    { "WW_Tz_SW",            &param_ww_tz_sw,            "%f" },
    { "SYS_Zykluszeit",      &param_sys_zykluszeit,      "%d" }
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

