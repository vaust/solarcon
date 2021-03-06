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

#ifndef _IO_PLC_H_
#define _IO_PLC_H_

#include "gen_types.h"

/**
 * @file io_pab_types.h
 * @brief Abbildung der Hardwarepunkte auf das Speicherabbild der KBus Klemmen.
 * @author Volker Stegmann
 */

/**
 * @brief Datenstruktur zur Zusammenfassung aller analogen Eingangsgroessen
 * (Temperaturen)
 */
typedef struct ain_s {
    temp10_pt1000_t  all_tau_mw;     /**< Aussentemperatur, AI, Pt1000                                     Slot 2, R1 */
    temp10_pt1000_t  sol_koll_t_mw;  /**< Kollektortemperatur, AI, Pt1000                                  Slot 2, R2 */
    temp10_pt1000_t  sol_sp1_tu_mw;  /**< Temperatur im Speicher 1 unten, AI, Pt1000                       Slot 2, R3 */
    temp10_pt1000_t  sol_sp1_to_mw;  /**< Temperatur im Speicher 1 oben, AI, Pt1000                        Slot 2, R4 */

    temp10_pt1000_t  sol_sp2_tu_mw;  /**< Temperatur im Speicher 2 unten, AI, Pt1000                       Slot 3, R1 */
    temp10_pt1000_t  sol_sp2_to_mw;  /**< Temperatur im Speicher 2 oben, AI, Pt1000                        Slot 3, R2 */
    temp10_pt1000_t  kes_tvl_mw;     /**< Kesselvorlauftemperatur, AI, Pt1000                              Slot 3, R3 */
    temp10_pt1000_t  kes_trl_mw;     /**< Kesselruecklauftemperatur, AI, Pt1000                            Slot 3, R4 */

    temp10_pt1000_t  hk_tvl_mw;      /**< Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000              Slot 4, R1 */
    temp10_pt1000_t  hk_trl_mw;      /**< Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000            Slot 4, R2 */
    temp10_pt1000_t  fb_prim_trl_mw; /**< Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000  Slot 4, R3 */
    temp10_pt1000_t  fb_sek_tvl_mw;  /**< Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000  Slot 4, R4 */

    temp10_pt1000_t  ww_hzg_tvl_mw;  /**< Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000                Slot 5, R1 */
    temp10_pt1000_t  ww_hzg_trl_mw;  /**< Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000              Slot 5, R2 */
    temp10_pt1000_t  ww_tww_mw;      /**< Warmwasser-Temperatur, AI, Pt1000                                Slot 5, R3 */
    temp10_pt1000_t  reserve;        /**< Ein Temperaturkanal als Reserve                                  Slot 5, R4 */
    u8_t             cnt1_status;    /**< Statusbyte des Zaehlers 1 angeschlossen an Wasserzaehler         Slot 13    */
    u8_t             align1;         /**< Align Byte (siehe WAGO Dokument zum 750.860 FBC Seite 156)                  */
    u8_t             cnt1_lsb;       /**< Lsb Zaehler 1                                                               */
    u8_t             cnt1_msb;       /**< Msb Zaehler 1                                                               */
    u8_t             cnt2_status;    /**< Statusbyte des Zaehlers 2 Reserve                                Slot 13,   */
    u8_t             align2;         /**< Align Byte (siehe WAGO Dokument zum 750.860 FBC Seite 156)                  */
    u8_t             cnt2_lsb;       /**< Lsb Zaehler 2                                                               */
    u8_t             cnt2_msb;       /**< Lsb Zaehler 2                                                               */
} ain_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller digitalen Eingangssgroessen
 */
typedef struct din_s {
    di_bitbyte_t     all_party   :1;  /**< FBH, Partyschalter, DI, Taster                                  Slot 1, I1 */
    di_bitbyte_t     kes_ssm     :1;  /**< Heizkessel Sammelstoermeldung, DI, 24V                          Slot 1, I2 */
    di_bitbyte_t     kes_br_bm   :1;  /**< Heizkessel Brennerbetriebsmeldung, DI, 24V                      Slot 1, I3 */
    di_bitbyte_t     fb_sek_tw   :1;  /**< Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V        Slot 1, I4 */

    di_bitbyte_t     ww_party    :1;  /**< Partyschalter, Warmwasserbereitung, DI, 24V                                */
    di_bitbyte_t     ww_wz_mw    :1;  /**< Warmwasserzaehler, DI, 24V                                                 */
    di_bitbyte_t     res2        :2;  /**< Byte auffuellen                                                            */
} din_t;

/**
 * @brief Zusammenfassung der Eingaenge
 */
typedef struct Control_Input_s {
    ain_t   ain;            /**< Zuerst die analogen Eingänge */
    din_t   din;            /**< Dann die digitalen Eingaenge */
} Control_Input_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller analogen Ausgangsgroessen (0-10V)
 */
typedef struct aout_s {
    ao_0_10V_t      kes_tvl_y;        /**< Kesselvorlauftemperaturvorgabe, AO, 0-10V                       Slot  9, O1 */
    ao_0_10V_t      hk_mv_y;          /**< Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V        Slot  9, O2 */
    ao_0_10V_t      fb_prim_mv_y;     /**< Fussbodenheizung, Primaerseite, Mischerventilanst., AO, 0-10V   Slot  9, O3 */
    ao_0_10V_t      ww_hzg_mv_y;      /**< Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V             Slot  9, O4 */
    ao_0_10V_t      ww_hzg_pu_y;      /**< Warmwasser, Heizungspumpe, Leistung, A0, 0-10V                  Slot 10, O1 */
    ao_0_10V_t      res1;
    ao_0_10V_t      res2;
    ao_0_10V_t      res3;
    /* Zaehlerklemme 750-638 belegt insgesamt 8 byte */
    u8_t            cnt1_steuer;      /**< Steuerbyte des Zaehlers                                         Slot 13,    */
    u8_t            align1;           /**< Align Byte (siehe WAGO Dokument zum 750.860 FBC Seite 156)                  */
    u8_t            cnt1_lsb;         /**< Lsb Zaehlervorgabe 1                                                        */
    u8_t            cnt1_msb;         /**< Msb ZaehlerZaehler 1                                                        */
    u8_t            cnt2_steuer;      /**< Statusbyte des Zaehlers                                         Slot 13,    */
    u8_t            align2;           /**< Align Byte (siehe WAGO Dokument zum 750-860 FBC Seite 156)                  */
    u8_t            cnt2_lsb;         /**< Lsb Zaehlervorgabe 2                                                        */
    u8_t            cnt2_msb;         /**< Msb ZaehlerZaehler 2                                                        */
} aout_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller digitalen Ausgangsgroessen
 */
typedef struct dout_s {
    do_bitbyte_t sol_pu_sb      :1;   /**< Solarkreislaufpumpe (ein/aus), DO, 24V+                          Slot 6, O1 */
    do_bitbyte_t sol_sp1_av_sb  :1;   /**< Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V +              Slot 6, O2 */
    do_bitbyte_t sol_sp2_av_sb  :1;   /**< Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V +              Slot 6, O3 */
    do_bitbyte_t kes_pu_sp1_sb  :1;   /**< Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V +                  Slot 6, O4 */

    do_bitbyte_t kes_pu_sp2_sb  :1;   /**< Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V +                  Slot 7, O1 */
    do_bitbyte_t hk_pu_sb       :1;   /**< Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V +                 Slot 7, O2 */
    do_bitbyte_t fb_prim_pu_sb  :1;   /**< Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V         Slot 7, O3 */
    do_bitbyte_t fb_sek_pu_sb   :1;   /**< Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V+      Slot 7, O4 */

    do_bitbyte_t ww_hzg_vv_sb   :1;   /**< Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V+ Slot 8, O1 */
    do_bitbyte_t ww_hzg_pu_sb   :1;   /**< Warmwasser, Heizungspumpe, (ein/aus), D0, 24V +                  Slot 8, O2 */
    do_bitbyte_t ww_zirk_pu_sb  :1;   /**< Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24V +              Slot 8, O3 */
    do_bitbyte_t res1           :1;   /**< reserviert fuer HK Heizkreis Mischventil                                    */

    do_bitbyte_t res2           :1;   /**< reserviert fuer Primaermischventil Fussbodenheizung              Slot 8, O4 */
    do_bitbyte_t res3           :1;   /**< reserviert fuer Primaermischventil Fussbodenheizung              Slot 8, O4 */
    do_bitbyte_t control_aktiv  :1;   /**< Kontrolllampe Steuerung aktiv                                               */
    do_bitbyte_t stoerung       :1;   /**< Kontrolllampe Sammelstoermeldung                                            */
} dout_t;

/**
 * @brief Zusammenfassung der Ausgaenge
 */
typedef struct Control_Output_s {
    aout_t  aout;
    dout_t  dout;
} Control_Output_t;

#define TF(x) ((float)(x)/10.0) 

#endif /* _IO_PLC_H_ */

