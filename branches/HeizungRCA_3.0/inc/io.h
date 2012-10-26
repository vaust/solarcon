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

#ifndef _IO_H_
#define _IO_H_

#include "gen_types.h"

/* <Prototypen> */
std_ret_t io_Read_ALL_Tau_MW( float *data );             /**< Aussentemperatur, AI, Pt1000     */
std_ret_t io_Read_ALL_PARTY( di_bitbyte_t *data );       /**< FBH, Partyschalter, DI, Taster   */
std_ret_t io_Read_SOL_KOLL_T_MW( float *data );          /**< Kollektortemperatur, AI, Pt1000  */
std_ret_t io_Read_SOL_SP1_Tu_MW( float *data );          /**< Temperatur im Speicher 1 unten, AI, Pt1000 */
std_ret_t io_Read_SOL_SP1_To_MW( float *data );          /**< Temperatur im Speicher 1 oben, AI, Pt1000  */
std_ret_t io_Read_SOL_SP2_Tu_MW( float *data );          /**< Temperatur im Speicher 2 unten, AI, Pt1000 */
std_ret_t io_Read_SOL_SP2_To_MW( float *data );          /**< Temperatur im Speicher 2 oben, AI, Pt1000  */
std_ret_t io_Write_SOL_PU_SB( do_bitbyte_t *data );      /**< Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_SOL_PU_SB( di_bitbyte_t *data );       /**< Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_SOL_SP1_AV_SB( di_bitbyte_t *data );  /**< Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_SOL_SP1_AV_SB( di_bitbyte_t *data );   /**< Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_SOL_SP2_AV_SB( di_bitbyte_t *data );  /**< Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_SOL_SP2_AV_SB( di_bitbyte_t *data );   /**< Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_KES_Tvl_MW( float *data );             /**< Kesselvorlauftemperatur, AI, Pt1000   */
std_ret_t io_Read_KES_Trl_MW( float *data );             /**< Kesselruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Write_KES_Tvl_Y( float *data );             /**< Kesselvorlauftemperaturvorgabe, AO, 0-10V */
std_ret_t io_Read_KES_Tvl_Y( float *data );              /**< Kesselvorlauftemperaturvorgabe, AO, 0-10V */
std_ret_t io_Write_KES_PU_SP1_SB( di_bitbyte_t *data );  /**< Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_KES_PU_SP1_SB( di_bitbyte_t *data );   /**< Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_KES_PU_SP2_SB( di_bitbyte_t *data );  /**< Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_KES_PU_SP2_SB( di_bitbyte_t *data );   /**< Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_KES_SSM( di_bitbyte_t *data );         /**< Heizkessel Sammelstoermeldung, DI, 24V */
std_ret_t io_Read_KES_BR_BM( di_bitbyte_t *data );       /**< Heizkessel Brennerbetriebsmeldung, DI, 24V */
std_ret_t io_Read_HK_Tvl_MW( float *data );              /**< Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000 */
std_ret_t io_Read_HK_Trl_MW( float *data );              /**< Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Write_HK_MV_Y( float *data );               /**< Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
std_ret_t io_Read_HK_MV_Y( float *data );                /**< Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
std_ret_t io_Write_HK_PU_SB( di_bitbyte_t *data );       /**< Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_HK_PU_SB( di_bitbyte_t *data );        /**< Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_FB_PRIM_Trl_MW( float *data );         /**< Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_FB_SEK_Tvl_MW( float *data );          /**< Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000 */
std_ret_t io_Write_FB_PRIM_MV_Y( float *data );          /**< Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
std_ret_t io_Read_FB_PRIM_MV_Y( float *data);            /**< Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
std_ret_t io_Write_FB_PRIM_PU_SB( di_bitbyte_t *data );  /**< Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_FB_PRIM_PU_SB( di_bitbyte_t *data );   /**< Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_FB_SEK_PU_SB( di_bitbyte_t *data );   /**< Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_FB_SEK_PU_SB( di_bitbyte_t *data );    /**< Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_FB_SEK_TW( di_bitbyte_t *data );       /**< Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
std_ret_t io_Read_WW_HZG_Tvl_MW( float *data );          /**< Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
std_ret_t io_Read_WW_HZG_Trl_MW( float *data );          /**< Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_WW_Tww_MW( float *data );              /**< Warmwasser-Temperatur, AI, Pt1000 */
std_ret_t io_Read_WW_WZ_MW( u16_t *data );               /**< Warmwasserzaehler, Zaehlereingang */
std_ret_t io_Write_WW_HZG_MV_Y( float *data );           /**< Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
std_ret_t io_Read_WW_HZG_MV_Y( float *data );            /**< Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
std_ret_t io_Write_WW_HZG_VV_SB( di_bitbyte_t *data );   /**< Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Read_WW_HZG_VV_SB( di_bitbyte_t *data );    /**< Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_WW_HZG_PU_SB( di_bitbyte_t *data );   /**< Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Read_WW_HZG_PU_SB( di_bitbyte_t *data );    /**< Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Write_WW_HZG_PU_Y( float *data );           /**< Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
std_ret_t io_Read_WW_HZG_PU_Y( float *data );            /**< Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
std_ret_t io_Write_WW_ZIRK_PU_SB( di_bitbyte_t *data );  /**< Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Read_WW_ZIRK_PU_SB( di_bitbyte_t *data );   /**< Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Read_WW_PARTY( di_bitbyte_t *data );        /**< Warmwasser, Partyschalter, DI, Taster  */
std_ret_t io_Write_STOERUNG( di_bitbyte_t *data );       /**< Gesamtstoermeldung */
std_ret_t io_Read_STOERUNG( di_bitbyte_t *data );        /**< Gesamtstoermeldung */
std_ret_t io_Write_CONTROL_AKTIV( di_bitbyte_t *data );  /**< Ausgang Steuerung aktiv */
std_ret_t io_Read_CONTROL_AKTIV( di_bitbyte_t *data );   /**< Ausgang Steuerung aktiv */
/* <Prototypen/> */
#endif /* _IO_H_ */



