#ifndef IO_H
#define IO_H

#undef _EXT_
#ifdef _MAIN_C_
    #define _EXT_
#else
    #define _EXT_ extern
#endif

/* Klartextnamen fuer die Klemmenvariablen */

#define ALL_Tau_MW      (pabIn_p->ain.all_tau_mw)       /* Aussentemperatur, AI, Pt1000     */
#define ALL_PARTY       (pabIn_p->din.all_party)        /* FBH, Partyschalter, DI, Taster   */

#define SOL_KOLL_T_MW   (pabIn_p->ain.sol_koll_t_mw)    /* Kollektortemperatur, AI, Pt1000  */
#define SOL_SP1_Tu_MW   (pabIn_p->ain.sol_sp1_tu_mw)    /* Temperatur im Speicher 1 unten, AI, Pt1000 */
#define SOL_SP1_To_MW   (pabIn_p->ain.sol_sp1_to_mw)    /* Temperatur im Speicher 1 oben, AI, Pt1000  */
#define SOL_SP2_Tu_MW   (pabIn_p->ain.sol_sp2_tu_mw)    /* Temperatur im Speicher 2 unten, AI, Pt1000 */
#define SOL_SP2_To_MW   (pabIn_p->ain.sol_sp2_to_mw)    /* Temperatur im Speicher 2 oben, AI, Pt1000  */
#define SOL_PU_SB       (pabOut_p->dout.sol_pu_sb)      /* Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
#define SOL_SP1_AV_SB   (pabOut_p->dout.sol_sp1_av_sb)  /* Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
#define SOL_SP2_AV_SB   (pabOut_p->dout.sol_sp2_av_sb)  /* Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */

#define KES_Tvl_MW      (pabIn_p->ain.kes_tvl_mw)       /* Kesselvorlauftemperatur, AI, Pt1000   */
#define KES_Trl_MW      (pabIn_p->ain.kes_trl_mw)       /* Kesselruecklauftemperatur, AI, Pt1000 */
#define KES_Tvl_Y       (pabOut_p->aout.kes_tvl_y)      /* Kesselvorlauftemperaturvorgabe, AO, 0-10V */
#define KES_PU_SP1_SB   (pabOut_p->dout.kes_pu_sp1_sb)  /* Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
#define KES_PU_SP2_SB   (pabOut_p->dout.kes_pu_sp2_sb)  /* Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
#define KES_SSM         (pabIn_p->din.kes_ssm)          /* Heizkessel Sammelstoermeldung, DI, 24V */
#define KES_BR_BM       (pabIn_p->din.kes_br_bm)        /* Heizkessel Brennerbetriebsmeldung, DI, 24V */

#define HK_Tvl_MW       (pabIn_p->ain.hk_tvl_mw)        /* Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000 */
#define HK_Trl_MW       (pabIn_p->ain.hk_trl_mw)        /* Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000 */
#define HK_MV_Y         (pabOut_p->aout.hk_mv_y)        /* Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
#define HK_PU_SB        (pabOut_p->dout.hk_pu_sb)       /* Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */

#define FB_PRIM_Trl_MW  (pabIn_p->ain.fb_prim_trl_mw)   /* Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000 */
#define FB_SEK_Tvl_MW   (pabIn_p->ain.fb_sek_tvl_mw)    /* Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000 */
#define FB_PRIM_MV_Y    (pabOut_p->aout.fb_prim_mv_y)   /* Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
#define FB_PRIM_PU_SB   (pabOut_p->dout.fb_prim_pu_sb)  /* Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
#define FB_SEK_PU_SB    (pabOut_p->dout.fb_sek_pu_sb)   /* Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
#define FB_SEK_TW       (pabIn_p->din.fb_sek_tw)        /* Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */

#define WW_HZG_Tvl_MW   (pabIn_p->ain.ww_hzg_tvl_mw)    /* Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
#define WW_HZG_Trl_MW   (pabIn_p->ain.ww_hzg_trl_mw)    /* Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
#define WW_Tww_MW       (pabIn_p->ain.ww_tww_mw)        /* Warmwasser-Temperatur, AI, Pt1000 */
#define WW_WZ_MW        (pabIn_p->din.ww_wz_mw)         /* Warmwasserzaehler, Impulse, DI, 24V */
#define WW_HZG_MV_Y     (pabOut_p->aout.ww_hzg_mv_y)    /* Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
#define WW_HZG_VV_SB    (pabOut_p->dout.ww_hzg_vv_sb)   /* Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
#define WW_HZG_PU_SB    (pabOut_p->dout.ww_hzg_pu_sb)   /* Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
#define WW_HZG_PU_Y     (pabOut_p->aout.ww_hzg_pu_y)    /* Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
#define WW_ZIRK_PU_SB   (pabOut_p->dout.ww_zirk_pu_sb)  /* Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
#define WW_PARTY        (pabIn_p->din.ww_party)         /* Warmwasser, Partyschalter, DI, Taster  */
#define STOERUNG        (pabOut_p->dout.stoerung)       /* Gesamtstörmeldung */
#define CONTROL_AKTIV   (pabOut_p->dout.control_aktiv)  /* Ausgang Steuerung aktiv */

/* Abbildung der Hardwarepunkte auf das Speicherabbild der KBus Klemmen: */

/* Temperaturen werden ueber Pt1000 Klemmen gemessen, die einen 16bit mit Vorzeichen ausgeben.  *
 * 0°C entspricht 0x0000 mit 0.1K entsprechend einem Bit                                        */

/* Eingangsgroessen */
typedef signed short temp10_pt1000_t;
typedef unsigned char di_bitbyte_t;

typedef struct {
    struct {
        temp10_pt1000_t     all_tau_mw;     /* Aussentemperatur, AI, Pt1000                                     Slot 2, R1 */
        temp10_pt1000_t     sol_koll_t_mw;  /* Kollektortemperatur, AI, Pt1000                                  Slot 2, R2 */
        temp10_pt1000_t     sol_sp1_tu_mw;  /* Temperatur im Speicher 1 unten, AI, Pt1000                       Slot 2, R3 */
        temp10_pt1000_t     sol_sp1_to_mw;  /* Temperatur im Speicher 1 oben, AI, Pt1000                        Slot 2, R4 */

        temp10_pt1000_t     sol_sp2_tu_mw;  /* Temperatur im Speicher 2 unten, AI, Pt1000                       Slot 3, R1 */
        temp10_pt1000_t     sol_sp2_to_mw;  /* Temperatur im Speicher 2 oben, AI, Pt1000                        Slot 3, R2 */
        temp10_pt1000_t     kes_tvl_mw;     /* Kesselvorlauftemperatur, AI, Pt1000                              Slot 3, R3 */
        temp10_pt1000_t     kes_trl_mw;     /* Kesselruecklauftemperatur, AI, Pt1000                            Slot 3, R4 */

        temp10_pt1000_t     hk_tvl_mw;      /* Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000              Slot 4, R1 */
        temp10_pt1000_t     hk_trl_mw;      /* Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000            Slot 4, R2 */
        temp10_pt1000_t     fb_prim_trl_mw; /* Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000  Slot 4, R3 */
        temp10_pt1000_t     fb_sek_tvl_mw;  /* Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000  Slot 4, R4 */

        temp10_pt1000_t     ww_hzg_tvl_mw;  /* Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000                Slot 5, R1 */
        temp10_pt1000_t     ww_hzg_trl_mw;  /* Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000              Slot 5, R2 */
        temp10_pt1000_t     ww_tww_mw;      /* Warmwasser-Temperatur, AI, Pt1000                                Slot 5, R3 */
        temp10_pt1000_t     reserve;        /* Ein Temperaturkanal als Reserve                                  Slot 5, R4 */
    } ain;
    struct {
        di_bitbyte_t    all_party   :1;     /* FBH, Partyschalter, DI, Taster                                   Slot 1, I1 */
        di_bitbyte_t    kes_ssm     :1;     /* Heizkessel Sammelstoermeldung, DI, 24V                           Slot 1, I2 */
        di_bitbyte_t    kes_br_bm   :1;     /* Heizkessel Brennerbetriebsmeldung, DI, 24V                       Slot 1, I3 */
        di_bitbyte_t    fb_sek_tw   :1;     /* Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V         Slot 1, I4 */

        di_bitbyte_t    ww_party    :1;     /* Partyschalter, Warmwasserbereitung, DI, 24V */
        di_bitbyte_t    ww_wz_mw    :1;     /* Warmwasserzaehler, DI, 24V                  */
        di_bitbyte_t    res2        :2;     /* Byte auffuellen */
    } din;
} Control_Input_t;

/* Ausgangsgroessen */
typedef signed short ao_0_10V_t;
typedef unsigned char do_bitbyte_t;

typedef struct {
    struct {
        ao_0_10V_t      kes_tvl_y;          /* Kesselvorlauftemperaturvorgabe, AO, 0-10V                        Slot  9, O1 */
        ao_0_10V_t      hk_mv_y;            /* Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V       Slot  9, O2 */
        ao_0_10V_t      fb_prim_mv_y;       /* Fussbodenheizung, Primaerseite, Mischerventilanst., AO, 0-10V    Slot  9, O3 */
        ao_0_10V_t      ww_hzg_mv_y;        /* Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V              Slot  9, O4 */
        ao_0_10V_t      ww_hzg_pu_y;        /* Warmwasser, Heizungspumpe, Leistung, A0, 0-10V                   Slot 10, O1 */
        ao_0_10V_t      res1;
        ao_0_10V_t      res2;
        ao_0_10V_t      res3;
    } aout;
    struct {
        do_bitbyte_t sol_pu_sb      :1;     /* Solarkreislaufpumpe (ein/aus), DO, 24V +                         Slot 6, O1 */
        do_bitbyte_t sol_sp1_av_sb  :1;     /* Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V +              Slot 6, O2 */
        do_bitbyte_t sol_sp2_av_sb  :1;     /* Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V +              Slot 6, O3 */
        do_bitbyte_t kes_pu_sp1_sb  :1;     /* Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V +                  Slot 6, O4 */

        do_bitbyte_t kes_pu_sp2_sb  :1;     /* Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V +                  Slot 7, O1 */
        do_bitbyte_t hk_pu_sb       :1;     /* Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V +                 Slot 7, O2 */
        do_bitbyte_t fb_prim_pu_sb  :1;     /* Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V         Slot 7, O3 */
        do_bitbyte_t fb_sek_pu_sb   :1;     /* Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V +     Slot 7, O4 */

        do_bitbyte_t ww_hzg_vv_sb   :1;     /* Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V + Slot 8, O1 */
        do_bitbyte_t ww_hzg_pu_sb   :1;     /* Warmwasser, Heizungspumpe, (ein/aus), D0, 24V +                  Slot 8, O2 */
        do_bitbyte_t ww_zirk_pu_sb  :1;     /* Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24V +              Slot 8, O3 */
        do_bitbyte_t res1           :1;     /* reserviert fuer HK Heizkreis Mischventil                                    */

        do_bitbyte_t res2           :1;     /* reserviert fuer Primaermischventil Fussbodenheizung              Slot 8, O4 */
        do_bitbyte_t res3           :1;     /* reserviert fuer Primaermischventil Fussbodenheizung              Slot 8, O4 */
        do_bitbyte_t control_aktiv  :1;     /* Kontrolllampe Steuerung aktiv    */
        do_bitbyte_t stoerung       :1;     /* Kontrolllampe Sammelstoermeldung */

        do_bitbyte_t res4           :8;     /* 8-DI Reserve */
    } dout;
} Control_Output_t;

/*
 *   PAB In:         00ffe060         PAB Size: 2040 bytes
 *   PAB Out:        00ffe858         PAB Size: 2040 bytes
*/

#define PAB_IN  ((volatile Control_Input_t  *) 0xFFE060)
#define PAB_OUT ((volatile Control_Output_t *) 0xFFE858)

#ifdef __WAGO__
#ifdef _MAIN_C_
volatile Control_Output_t    *pabOut_p = PAB_OUT;
volatile Control_Input_t     *pabIn_p  = PAB_IN;
#else
extern volatile Control_Output_t    *pabOut_p;
extern volatile Control_Input_t     *pabIn_p;
#endif
#else
_EXT_ volatile Control_Output_t    pab_Dbg_Out;
_EXT_ volatile Control_Input_t     pab_Dbg_In;
#ifdef _MAIN_C_
volatile Control_Output_t    *pabOut_p = &pab_Dbg_Out;
volatile Control_Input_t     *pabIn_p  = &pab_Dbg_In;
#else
extern volatile Control_Output_t    *pabOut_p;
extern volatile Control_Input_t     *pabIn_p;
#endif
#endif

#define VFULLSCALE      0x7FFF
#define IO_EIN          0x01
#define IO_AUS          0x00
#define IO_AUF          0x01
#define IO_ZU           0x00
/* Verteilventilstellungen (noch zu testen !) */
#define IO_VV_SP1       0x00
#define IO_VV_SP2       0x01

#define MAX_Y_PCT       99.9
#define MIN_Y_PCT        0.1

#endif
