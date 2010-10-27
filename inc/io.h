#ifndef _IO_H_
#define _IO_H_

#include "gen_types.h"

#ifdef _IO_C_ 

/* Temperaturen werden ueber Pt1000 Klemmen gemessen, die einen 16bit mit Vorzeichen ausgeben.  *
 * 0°C entspricht 0x0000 mit 0.1K entsprechend einem Bit                                        */
#define TF(x) ((float)(x)/10.0) 

/* Abbildung der Hardwarepunkte auf das Speicherabbild der KBus Klemmen: */

/* Eingangsgroessen */
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
        do_bitbyte_t sol_pu_sb      :1;     /* Solarkreislaufpumpe (ein/aus), DO, 24V+                          Slot 6, O1 */
        do_bitbyte_t sol_sp1_av_sb  :1;     /* Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V+               Slot 6, O2 */
        do_bitbyte_t sol_sp2_av_sb  :1;     /* Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V +              Slot 6, O3 */
        do_bitbyte_t kes_pu_sp1_sb  :1;     /* Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V +                  Slot 6, O4 */

        do_bitbyte_t kes_pu_sp2_sb  :1;     /* Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V +                  Slot 7, O1 */
        do_bitbyte_t hk_pu_sb       :1;     /* Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V +                 Slot 7, O2 */
        do_bitbyte_t fb_prim_pu_sb  :1;     /* Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V         Slot 7, O3 */
        do_bitbyte_t fb_sek_pu_sb   :1;     /* Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V+      Slot 7, O4 */

        do_bitbyte_t ww_hzg_vv_sb   :1;     /* Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V+ Slot 8, O1 */
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
volatile Control_Output_t    *pabOut_p = PAB_OUT;
volatile Control_Input_t     *pabIn_p  = PAB_IN;
#else /* __WAGO__ */
volatile Control_Output_t    pab_Dbg_Out;
volatile Control_Input_t     pab_Dbg_In;
volatile Control_Output_t    *pabOut_p = &pab_Dbg_Out;
volatile Control_Input_t     *pabIn_p  = &pab_Dbg_In;
#endif /* __WAGO__ */

#define AO_FULLSCALE         0x8000

#endif /* _IO_C_ */

/* <Prototypen> */
float io_get_ALL_Tau_MW( void );                        /**< Aussentemperatur, AI, Pt1000     */
u8_t io_get_ALL_PARTY( void );                          /**< FBH, Partyschalter, DI, Taster   */
float io_get_SOL_KOLL_T_MW( void );                     /**< Kollektortemperatur, AI, Pt1000  */
float io_get_SOL_SP1_Tu_MW( void );                     /**< Temperatur im Speicher 1 unten, AI, Pt1000 */
float io_get_SOL_SP1_To_MW( void );                     /**< Temperatur im Speicher 1 oben, AI, Pt1000  */
float io_get_SOL_SP2_Tu_MW( void );                     /**< Temperatur im Speicher 2 unten, AI, Pt1000 */
float io_get_SOL_SP2_To_MW( void );                     /**< Temperatur im Speicher 2 oben, AI, Pt1000  */
di_bitbyte_t io_put_SOL_PU_SB( do_bitbyte_t sb );       /**< Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_SOL_PU_SB( void );                  /**< Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_SOL_SP1_AV_SB( do_bitbyte_t sb );   /**< Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_SOL_SP1_AV_SB( void );              /**< Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_SOL_SP2_AV_SB( do_bitbyte_t sb );   /**< Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_SOL_SP2_AV_SB( void );              /**< Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
float io_get_KES_Tvl_MW( void );                        /**< Kesselvorlauftemperatur, AI, Pt1000   */
float io_get_KES_Trl_MW( void );                        /**< Kesselruecklauftemperatur, AI, Pt1000 */
void io_put_KES_Tvl_Y( float pct );                     /**< Kesselvorlauftemperaturvorgabe, AO, 0-10V */    
float io_get_KES_Tvl_Y( void );                         /**< Kesselvorlauftemperaturvorgabe, AO, 0-10V */    
di_bitbyte_t io_put_KES_PU_SP1_SB( do_bitbyte_t sb );   /**< Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_KES_PU_SP1_SB( void );              /**< Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_KES_PU_SP2_SB( do_bitbyte_t sb );   /**< Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */    
di_bitbyte_t io_get_KES_PU_SP2_SB( void );              /**< Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */    
di_bitbyte_t io_get_KES_SSM( void );                    /**< Heizkessel Sammelstoermeldung, DI, 24V */
di_bitbyte_t io_get_KES_BR_BM( void );                  /**< Heizkessel Brennerbetriebsmeldung, DI, 24V */
float io_get_HK_Tvl_MW( void );                         /**< Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000 */    
float io_get_HK_Trl_MW( void );                         /**< Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000 */
void io_put_HK_MV_Y( float pct );                       /**< Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
float io_get_HK_MV_Y( void );                           /**< Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
di_bitbyte_t io_put_HK_PU_SB( do_bitbyte_t sb );        /**< Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */    
di_bitbyte_t io_get_HK_PU_SB( void );                   /**< Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */    
float io_get_FB_PRIM_Trl_MW( void );                    /**< Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000 */
float io_get_FB_SEK_Tvl_MW( void );                     /**< Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000 */
void io_put_FB_PRIM_MV_Y( float pct );                  /**< Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
float io_get_FB_PRIM_MV_Y( void );                      /**< Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
di_bitbyte_t io_put_FB_PRIM_PU_SB( do_bitbyte_t sb );   /**< Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_FB_PRIM_PU_SB( void );              /**< Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_FB_SEK_PU_SB( do_bitbyte_t sb );    /**< Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_FB_SEK_PU_SB( void );               /**< Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_FB_SEK_TW( void );                  /**< Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
float io_get_WW_HZG_Tvl_MW( void );                     /**< Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
float io_get_WW_HZG_Trl_MW( void );                     /**< Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
float io_get_WW_Tww_MW( void );                         /**< Warmwasser-Temperatur, AI, Pt1000 */
u32_t io_get_WW_WZ_MW( void );                          /**< Warmwasserzaehler, Zaehlereingang */
void io_put_WW_HZG_MV_Y( float pct );                   /**< Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
float io_get_WW_HZG_MV_Y( void );                       /**< Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
di_bitbyte_t io_put_WW_HZG_VV_SB( do_bitbyte_t sb );    /**< Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_get_WW_HZG_VV_SB( void );               /**< Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_WW_HZG_PU_SB( do_bitbyte_t sb );    /**< Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
di_bitbyte_t io_get_WW_HZG_PU_SB( void );               /**< Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
void io_put_WW_HZG_PU_Y( float pct );                   /**< Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
float io_get_WW_HZG_PU_Y( void );                       /**< Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
di_bitbyte_t io_put_WW_ZIRK_PU_SB( do_bitbyte_t sb );   /**< Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
di_bitbyte_t io_get_WW_ZIRK_PU_SB( void );              /**< Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
di_bitbyte_t io_get_WW_PARTY( void );                   /**< Warmwasser, Partyschalter, DI, Taster  */   
di_bitbyte_t io_put_STOERUNG( do_bitbyte_t sb );        /**< Gesamtstörmeldung */
di_bitbyte_t io_get_STOERUNG( void );                   /**< Gesamtstörmeldung */
di_bitbyte_t io_put_CONTROL_AKTIV( do_bitbyte_t sb );   /**< Ausgang Steuerung aktiv */    
di_bitbyte_t io_get_CONTROL_AKTIV( void );              /**< Ausgang Steuerung aktiv */    
/* <Prototypen/> */

#endif /* _IO_H_ */



