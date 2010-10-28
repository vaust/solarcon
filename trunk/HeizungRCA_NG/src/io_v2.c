#define _IO_V2_C_

#include "gen_types.h"
#include "io_plc.h"
#include "io_v2.h"


static
void io_InitTemperaturSensor( io_tempsens_obj_t *obj,
                               float             messbereich_anfang,
                               float             messbereich_ende,
                               // float             aufloesung,
                               io_obj_status_t   status,
                               temp10_pt1000_t   *kbus_adresse_p
                              )
{
    obj->messbereich_anfang = messbereich_anfang;
    obj->messbereich_ende   = messbereich_ende;
 //   obj->aufloesung         = aufloesung;
    obj->status             = status;
    obj->kbus_adresse_p     = kbus_adresse_p;
}

void io_InitAlleTemperaturSensoren( void )
{
    io_InitTemperaturSensor( &io_ALL_Tau_MW    , -50.0,  50.0, zNormal, &(pabIn_p->ain.all_tau_mw) );
    io_InitTemperaturSensor( &io_SOL_KOLL_T_MW , -50.0, 150.0, zNormal, &(pabIn_p->ain.sol_koll_t_mw) );
    io_InitTemperaturSensor( &io_SOL_SP1_Tu_MW ,   0.0, 150.0, zNormal, &(pabIn_p->ain.sol_sp1_tu_mw) );
    io_InitTemperaturSensor( &io_SOL_SP1_To_MW ,   0.0, 150.0, zNormal, &(pabIn_p->ain.sol_sp1_to_mw) );
    io_InitTemperaturSensor( &io_SOL_SP2_Tu_MW ,   0.0, 150.0, zNormal, &(pabIn_p->ain.sol_sp2_tu_mw) );
    io_InitTemperaturSensor( &io_SOL_SP2_To_MW ,   0.0, 150.0, zNormal, &(pabIn_p->ain.sol_sp2_to_mw) );
    io_InitTemperaturSensor( &io_KES_Tvl_MW    ,   0.0, 100.0, zNormal, &(pabIn_p->ain.kes_tvl_mw) );
    io_InitTemperaturSensor( &io_KES_Trl_MW    ,   0.0, 100.0, zNormal, &(pabIn_p->ain.kes_trl_mw) );
    io_InitTemperaturSensor( &io_HK_Tvl_MW     ,   0.0, 100.0, zNormal, &(pabIn_p->ain.hk_tvl_mw) );
    io_InitTemperaturSensor( &io_HK_Trl_MW     ,   0.0, 100.0, zNormal, &(pabIn_p->ain.hk_trl_mw) );
    io_InitTemperaturSensor( &io_FB_PRIM_Trl_MW,   0.0, 100.0, zNormal, &(pabIn_p->ain.fb_prim_trl_mw) );
    io_InitTemperaturSensor( &io_FB_SEK_Tvl_MW ,   0.0, 100.0, zNormal, &(pabIn_p->ain.fb_sek_tvl_mw) );
    io_InitTemperaturSensor( &io_WW_HZG_Tvl_MW ,   0.0, 100.0, zNormal, &(pabIn_p->ain.ww_hzg_tvl_mw) );
    io_InitTemperaturSensor( &io_WW_HZG_Trl_MW ,   0.0, 100.0, zNormal, &(pabIn_p->ain.ww_hzg_trl_mw) );
    io_InitTemperaturSensor( &io_WW_Tww_MW     ,   0.0, 100.0, zNormal, &(pabIn_p->ain.ww_tww_mw) );
}

/** \brief Methode zur Abfrage der Temperaturmessstellen.
  * Der Messwert wird in de Objektstruktur abgelegt und im Normalfall auch zurückgeben.
  * Bei unplausiblen Messwerten wird der rohe Messwert zurückgegeben und in der Objektstruktur
  * die jeweilige Messbereichsgrenze abgelegt, so dass noch sinnvoll weitergerechnet werden kann
  * \param this Pointer auf ein Temperaturmessobjekt
  */

float io_MesseTemperatur( io_tempsens_obj_t *this )
{
    float temp_val;

    switch( this->status ) {
        case obj_ManuelleZuweisung:
            temp_val = this->messwert;
            break;
        case obj_Normal:
            temp_val = TF(*(obj->kbus_adresse_p));
            if( temp_val < IO_MIN_TEMP ) {
                this->status = obj_Kurzschluss;
                temp_val = this->messwert;          /* in diesem Fall alten Messwert behalten */
            }
            else if( temp_val < this->messbereich_anfang ) {
                this->status = obj_Unplausibel;
                this->messwert = this->messbereich_anfang;
            }
            else if( temp_val > IO_MAX_TEMP ) {
                this->status = obj_Kabelbruch;
                temp_val = this->messwert;          /* in diesem Fall alten Messwert behalten */

            else if( temp_val > obj->messbereich_ende ) {
                this->status = obj_Unplausibel;
                this->messwert = obj->messbereich_ende;
            }
            else {
                this->status = obj_Normal;  /* Nur solange Messwert in den Grenzen liegt bleibt der Zustand normal */
                this->messwert = temp_val;
            }
            break;
        case default:
            temp_val = this->messwert;  /* in diesem Fall alten Messwert behalten */
            break;
    }
    return (temp_val);
}


/** FBH, Partyschalter, DI, Taster   */
u8_t io_get_ALL_PARTY( void )
{
    return (pabIn_p->din.all_party);
}

/** Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_SOL_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_pu_sb = sb;
    return (pabOut_p->dout.sol_pu_sb);
}

di_bitbyte_t io_get_SOL_PU_SB( void )
{
    return (pabOut_p->dout.sol_pu_sb);
}

/** Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_SOL_SP1_AV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_sp1_av_sb = sb;
    return (pabOut_p->dout.sol_sp1_av_sb);
}

di_bitbyte_t io_get_SOL_SP1_AV_SB( void )
{
    return (pabOut_p->dout.sol_sp1_av_sb);
}

/** Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_SOL_SP2_AV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_sp2_av_sb = sb;
    return (pabOut_p->dout.sol_sp2_av_sb);
}

di_bitbyte_t io_get_SOL_SP2_AV_SB( void )
{
    return (pabOut_p->dout.sol_sp2_av_sb);
}

/** Kesselvorlauftemperaturvorgabe, AO, 0-10V */
void io_put_KES_Tvl_Y( float pct )
{
    pabOut_p->aout.kes_tvl_y = (pct*AO_FULLSCALE)/100;
}

float io_get_KES_Tvl_Y( void )
{
    return ((float)pabOut_p->aout.kes_tvl_y/AO_FULLSCALE * 100.0); /* % */
}

/** Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_KES_PU_SP1_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.kes_pu_sp1_sb = sb;
    return (pabOut_p->dout.kes_pu_sp1_sb);
}

di_bitbyte_t io_get_KES_PU_SP1_SB( void )
{
    return (pabOut_p->dout.kes_pu_sp1_sb);
}

/** Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_KES_PU_SP2_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.kes_pu_sp2_sb = sb;
    return (pabOut_p->dout.kes_pu_sp2_sb);
}

di_bitbyte_t io_get_KES_PU_SP2_SB( void )
{
    return (pabOut_p->dout.kes_pu_sp2_sb);
}

/** Heizkessel Sammelstoermeldung, DI, 24V */
di_bitbyte_t io_get_KES_SSM( void )
{
    return (pabIn_p->din.kes_ssm);
}

/** Heizkessel Brennerbetriebsmeldung, DI, 24V */
di_bitbyte_t io_get_KES_BR_BM( void )
{
    return (pabIn_p->din.kes_br_bm);
}

/** Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
void io_put_HK_MV_Y( float pct )
{
    pabOut_p->aout.hk_mv_y = (pct*AO_FULLSCALE)/100;
}

float io_get_HK_MV_Y( void )
{
    return ((float)pabOut_p->aout.hk_mv_y/AO_FULLSCALE * 100.0); /* % */
}

/** Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_HK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.hk_pu_sb = sb;
    return (pabOut_p->dout.hk_pu_sb);
}

di_bitbyte_t io_get_HK_PU_SB( void )
{
    return (pabOut_p->dout.hk_pu_sb);
}

/** Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
void io_put_FB_PRIM_MV_Y( float pct )
{
    pabOut_p->aout.fb_prim_mv_y = (pct*AO_FULLSCALE)/100;
}

float io_get_FB_PRIM_MV_Y( void )
{
    return ((float)pabOut_p->aout.fb_prim_mv_y/AO_FULLSCALE * 100.0); /* % */
}

/** Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_FB_PRIM_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.fb_prim_pu_sb = sb;
    return (pabOut_p->dout.fb_prim_pu_sb);
}

di_bitbyte_t io_get_FB_PRIM_PU_SB( void )
{
    return (pabOut_p->dout.fb_prim_pu_sb);
}

/** Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_FB_SEK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.fb_sek_pu_sb = sb;
    return (pabOut_p->dout.fb_sek_pu_sb);
}

di_bitbyte_t io_get_FB_SEK_PU_SB( void )
{
    return (pabOut_p->dout.fb_sek_pu_sb);
}

/** Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
di_bitbyte_t io_get_FB_SEK_TW( void )
{
    return (pabIn_p->din.fb_sek_tw);
}

/** Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
float io_get_WW_HZG_Tvl_MW( void )
{
    return TF(pabIn_p->ain.ww_hzg_tvl_mw);
}

/** Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
float io_get_WW_HZG_Trl_MW( void )
{
    return TF(pabIn_p->ain.ww_hzg_trl_mw);
}

/** Warmwasser-Temperatur, AI, Pt1000 */
float io_get_WW_Tww_MW( void )
{
    return TF(pabIn_p->ain.ww_tww_mw);
}

/** Warmwasserzaehler, Zaehlereingang */
u32_t io_get_WW_WZ_MW( void )
{
    // TODO:    return (pabIn_p->din.ww_wz_mw)
    return 9999;
}

/** Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
void io_put_WW_HZG_MV_Y( float pct )
{
    pabOut_p->aout.ww_hzg_mv_y = (pct*AO_FULLSCALE)/100;
}

float io_get_WW_HZG_MV_Y( void )
{
    return ((float)pabOut_p->aout.ww_hzg_mv_y/AO_FULLSCALE * 100.0); /* % */

}

/** Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
di_bitbyte_t io_put_WW_HZG_VV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_hzg_vv_sb = sb;
    return (pabOut_p->dout.ww_hzg_vv_sb);
}

di_bitbyte_t io_get_WW_HZG_VV_SB( void )
{
    return (pabOut_p->dout.ww_hzg_vv_sb);
}

/** Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
di_bitbyte_t io_put_WW_HZG_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_hzg_pu_sb = sb;
    return (pabOut_p->dout.ww_hzg_pu_sb);
}

di_bitbyte_t io_get_WW_HZG_PU_SB( void )
{
    return (pabOut_p->dout.ww_hzg_pu_sb);
}

/** Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
void io_put_WW_HZG_PU_Y( float pct )
{
    pabOut_p->aout.ww_hzg_pu_y = (pct*AO_FULLSCALE)/100;
}

float io_get_WW_HZG_PU_Y( void )
{
    return ((float)pabOut_p->aout.ww_hzg_pu_y/AO_FULLSCALE * 100.0); /* % */
}

/** Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
di_bitbyte_t io_put_WW_ZIRK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_zirk_pu_sb = sb;
    return (pabOut_p->dout.ww_zirk_pu_sb);
}

di_bitbyte_t io_get_WW_ZIRK_PU_SB( void )
{
    return (pabOut_p->dout.ww_zirk_pu_sb);
}

/** Warmwasser, Partyschalter, DI, Taster  */
di_bitbyte_t io_get_WW_PARTY( void )
{
    return (pabIn_p->din.ww_party);
}

/** Gesamtstörmeldung */
di_bitbyte_t io_put_STOERUNG( do_bitbyte_t sb )
{
    pabOut_p->dout.stoerung = sb;
    return (pabOut_p->dout.stoerung);
}

di_bitbyte_t io_get_STOERUNG( void )
{
    return (pabOut_p->dout.stoerung);
}

/** Ausgang Steuerung aktiv */
di_bitbyte_t io_put_CONTROL_AKTIV( do_bitbyte_t sb )
{
    pabOut_p->dout.control_aktiv = sb;
    return (pabOut_p->dout.control_aktiv);
}

di_bitbyte_t io_get_CONTROL_AKTIV( void )
{
    return (pabOut_p->dout.control_aktiv);
}

