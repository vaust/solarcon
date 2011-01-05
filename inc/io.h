#ifndef _IO_H_
#define _IO_H_

#include "gen_types.h"

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



