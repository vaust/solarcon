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

#define _IO_C_

#include "gen_types.h"
#include "io_wago_hwif.h"
#include "io_pab_types.h"
#include "io.h"

/**
 * @file io.c
 * @brief Interfacemethoden zum Lesen und Schreiben des Prozessabbildes
 * @author Volker Stegmann
 */

/*
 * Temperaturen werden ueber Pt1000 Klemmen gemessen, die einen 16bit Wert
 * mit Vorzeichen ausgeben. 0°C entspricht 0x0000 mit 0.1K entsprechend einem Bit.
 */

/** Aussentemperatur, AI, Pt1000     */
std_ret_t io_Read_ALL_Tau_MW( float *data )
{
    *data = TF(pabIn_p->ain.all_tau_mw);
    return E_OK;
}

/** FBH, Partyschalter, DI, Taster   */
std_ret_t io_Read_ALL_PARTY( di_bitbyte_t *data )
{
    *data = pabIn_p->din.all_party;
    return E_OK;
}

/** Kollektortemperatur, AI, Pt1000  */
std_ret_t io_Read_SOL_KOLL_T_MW( float *data )
{
    *data = TF(pabIn_p->ain.sol_koll_t_mw);
    return E_OK;
}

/** Temperatur im Speicher 1 unten, AI, Pt1000 */
std_ret_t io_Read_SOL_SP1_Tu_MW( float *data )
{
    *data = TF(pabIn_p->ain.sol_sp1_tu_mw);
    return E_OK;
}

/** Temperatur im Speicher 1 oben, AI, Pt1000  */
std_ret_t io_Read_SOL_SP1_To_MW( float *data )
{
    *data = TF(pabIn_p->ain.sol_sp1_to_mw);
    return E_OK;
}

/** Temperatur im Speicher 2 unten, AI, Pt1000 */
std_ret_t io_Read_SOL_SP2_Tu_MW( float *data )
{
    *data = TF(pabIn_p->ain.sol_sp2_tu_mw);
    return E_OK;
}

/** Temperatur im Speicher 2 oben, AI, Pt1000  */
std_ret_t io_Read_SOL_SP2_To_MW( float *data )
{
   *data = TF(pabIn_p->ain.sol_sp2_to_mw);
   return E_OK;
}

/** Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_SOL_PU_SB( do_bitbyte_t *data )
{
    pabOut_p->dout.sol_pu_sb = *data;
    return E_OK;
}

std_ret_t io_Read_SOL_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.sol_pu_sb;
    return E_OK;
}

/** Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_SOL_SP1_AV_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.sol_sp1_av_sb = *data;
    return E_OK;
}

std_ret_t io_Read_SOL_SP1_AV_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.sol_sp1_av_sb;
    return E_OK;
}

/** Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_SOL_SP2_AV_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.sol_sp2_av_sb = *data;
    return E_OK;
}

std_ret_t io_Read_SOL_SP2_AV_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.sol_sp2_av_sb)
    return E_OK;
}

/** Kesselvorlauftemperatur, AI, Pt1000   */
std_ret_t io_Read_KES_Tvl_MW( float *data )
{
    *data = TF(pabIn_p->ain.kes_tvl_mw);
    return E_OK;
}

/** Kesselruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_KES_Trl_MW( float *data )
{
    *data = TF(pabIn_p->ain.kes_trl_mw);
    return E_OK;
}

/** Kesselvorlauftemperaturvorgabe, AO, 0-10V */
std_ret_t io_Write_KES_Tvl_Y( float *data )
{
    pabOut_p->aout.kes_tvl_y = (ao_0_10V_t) ((*data * AO_FULLSCALE)/100);
    return E_OK;
}

std_ret_t io_Read_KES_Tvl_Y( float *data )
{
    *data = ((float)pabOut_p->aout.kes_tvl_y/AO_FULLSCALE * 100.0); /* % */
    return E_OK;
}

/** Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_KES_PU_SP1_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.kes_pu_sp1_sb = *data;
    return E_OK;
}

std_ret_t io_Read_KES_PU_SP1_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.kes_pu_sp1_sb;
    return E_OK;
}

/** Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_KES_PU_SP2_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.kes_pu_sp2_sb = *data;
    return E_OK;
}

std_ret_t io_Read_KES_PU_SP2_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.kes_pu_sp2_sb;
    return E_OK;
}

/** Heizkessel Sammelstoermeldung, DI, 24V */
std_ret_t io_Read_KES_SSM( di_bitbyte_t *data )
{
    *data = pabIn_p->din.kes_ssm;
    return E_OK;
}

/** Heizkessel Brennerbetriebsmeldung, DI, 24V */
std_ret_t io_Read_KES_BR_BM( di_bitbyte_t *data )
{
    *data = pabIn_p->din.kes_br_bm;
    return E_OK;
}

/** Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000 */
std_ret_t io_Read_HK_Tvl_MW( float *data )
{
    *data = TF(pabIn_p->ain.hk_tvl_mw);
    return E_OK;
}

/** Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_HK_Trl_MW( float *data )
{
    *data = TF(pabIn_p->ain.hk_trl_mw);
}

/** Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
std_ret_t io_Write_HK_MV_Y( float *data )
{
    pabOut_p->aout.hk_mv_y = (ao_0_10V_t) ((*data *AO_FULLSCALE)/100);
    return E_OK;
}

std_ret_t io_Read_HK_MV_Y( float *data )
{
    *data = ((float)pabOut_p->aout.hk_mv_y/AO_FULLSCALE * 100.0); /* % */
    return E_OK;
}

/** Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_HK_PU_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.hk_pu_sb = *data;
    return E_OK;
}

std_ret_t io_Read_HK_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.hk_pu_sb;
    return E_OK;
}

/** Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_FB_PRIM_Trl_MW( float *data )
{
    *data = TF(pabIn_p->ain.fb_prim_trl_mw);
    return E_OK;
}

/** Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000 */
std_ret_t io_Read_FB_SEK_Tvl_MW( float *data )
{
    *data = TF(pabIn_p->ain.fb_sek_tvl_mw);
    return E_OK;
}

/** Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
std_ret_t io_Write_FB_PRIM_MV_Y( float *data )
{
    pabOut_p->aout.fb_prim_mv_y = (ao_0_10V_t) ((*data *AO_FULLSCALE)/100);
}

std_ret_t io_Read_FB_PRIM_MV_Y( float *data)
{
    *data = (float)pabOut_p->aout.fb_prim_mv_y/AO_FULLSCALE * 100.0; /* % */
    return E_OK;
}

/** Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_FB_PRIM_PU_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.fb_prim_pu_sb = *data;
    return E_OK;
}

std_ret_t io_Read_FB_PRIM_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.fb_prim_pu_sb;
    return E_OK;
}

/** Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_FB_SEK_PU_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.fb_sek_pu_sb = *data;
    return E_OK;
}

std_ret_t io_Read_FB_SEK_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.fb_sek_pu_sb;
    return E_OK;
}

/** Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
std_ret_t io_Read_FB_SEK_TW( di_bitbyte_t *data )
{
    *data = pabIn_p->din.fb_sek_tw;
    return E_OK;
}

/** Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
std_ret_t io_Read_WW_HZG_Tvl_MW( float *data )
{
    *data = TF(pabIn_p->ain.ww_hzg_tvl_mw);
    return E_OK;
}

/** Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
std_ret_t io_Read_WW_HZG_Trl_MW( float *data )
{
    *data = TF(pabIn_p->ain.ww_hzg_trl_mw);
    return E_OK;
}

/** Warmwasser-Temperatur, AI, Pt1000 */
std_ret_t io_Read_WW_Tww_MW( float *data )
{
    *data = TF(pabIn_p->ain.ww_tww_mw);
    return E_OK;
}

/** Warmwasserzaehler, Zaehlereingang */
std_ret_t io_Read_WW_WZ_MW( u16_t *data )
{
    *data = (u16_t)pabIn_p->ain.cnt1_lsb + ((u16_t)pabIn_p->ain.cnt1_msb << 8);
    return E_OK;
}

/** Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
std_ret_t io_Write_WW_HZG_MV_Y( float *data )
{
    pabOut_p->aout.ww_hzg_mv_y = (*data *AO_FULLSCALE)/100;
    return E_OK;
}

std_ret_t io_Read_WW_HZG_MV_Y( float *data )
{
    *data = (float)pabOut_p->aout.ww_hzg_mv_y/AO_FULLSCALE * 100.0; /* % */
    return E_OK;
}

/** Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
std_ret_t io_Write_WW_HZG_VV_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.ww_hzg_vv_sb = *data;
    return E_OK;
}

std_ret_t io_Read_WW_HZG_VV_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.ww_hzg_vv_sb;
    return E_OK;
}

/** Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Write_WW_HZG_PU_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.ww_hzg_pu_sb = sb;
    return (pabOut_p->dout.ww_hzg_pu_sb);
}

std_ret_t io_Read_WW_HZG_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.ww_hzg_pu_sb;
    return E_OK;
}

/** Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
std_ret_t io_Write_WW_HZG_PU_Y( float *data )
{
    pabOut_p->aout.ww_hzg_pu_y = (*data *AO_FULLSCALE)/100;
    return E_OK;
}

std_ret_t io_Read_WW_HZG_PU_Y( float *data )
{
    *data = (float)pabOut_p->aout.ww_hzg_pu_y/AO_FULLSCALE * 100.0; /* % */
    return E_OK;
}

/** Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
std_ret_t io_Write_WW_ZIRK_PU_SB( di_bitbyte_t *data )
{
    pabOut_p->dout.ww_zirk_pu_sb = *data;
    return E_OK;
}

std_ret_t io_Read_WW_ZIRK_PU_SB( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.ww_zirk_pu_sb;
    return E_OK;
}

/** Warmwasser, Partyschalter, DI, Taster  */
std_ret_t io_Read_WW_PARTY( di_bitbyte_t *data )
{
    *data = pabIn_p->din.ww_party;
    return E_OK;
}

/** Gesamtstoermeldung */
std_ret_t io_Write_STOERUNG( di_bitbyte_t *data )
{
    pabOut_p->dout.stoerung = *data;
    return E_OK;
}

std_ret_t io_Read_STOERUNG( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.stoerung;
    return E_OK;
}

/** Ausgang Steuerung aktiv */
std_ret_t io_Write_CONTROL_AKTIV( di_bitbyte_t *data )
{
    pabOut_p->dout.control_aktiv = *data;
    return E_OK;
}

std_ret_t io_Read_CONTROL_AKTIV( di_bitbyte_t *data )
{
    *data = pabOut_p->dout.control_aktiv;
    return E_OK;
}
