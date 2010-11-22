#define _IO_V2_C_
#define _IO_C_

#include "gen_types.h"
#include "io_plc.h"
#include "io.h"
#include "io_v2.h"

static  
void io_InitTemp( io_temp_obj_t     *self,
                  float             messbereich_anfang,
                  float             messbereich_ende,
                  temp10_pt1000_t   *kbus_adresse_p )
{
    self->messbereich_anfang = messbereich_anfang;
    self->messbereich_ende   = messbereich_ende;
    self->status             = io_Normal;
    self->kbus_adresse_p     = kbus_adresse_p;
}

void io_InitTempAll( void )
{
    io_InitTemp( &io_ALL_Tau_MW    , -50.0,  50.0, (temp10_pt1000_t *) &(pabIn_p->ain.all_tau_mw) );
    io_InitTemp( &io_SOL_KOLL_T_MW , -50.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_koll_t_mw) );
    io_InitTemp( &io_SOL_SP1_Tu_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp1_tu_mw) );
    io_InitTemp( &io_SOL_SP1_To_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp1_to_mw) );
    io_InitTemp( &io_SOL_SP2_Tu_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp2_tu_mw) );
    io_InitTemp( &io_SOL_SP2_To_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp2_to_mw) );
    io_InitTemp( &io_KES_Tvl_MW    ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.kes_tvl_mw) );
    io_InitTemp( &io_KES_Trl_MW    ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.kes_trl_mw) );
    io_InitTemp( &io_HK_Tvl_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.hk_tvl_mw) );
    io_InitTemp( &io_HK_Trl_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.hk_trl_mw) );
    io_InitTemp( &io_FB_PRIM_Trl_MW,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.fb_prim_trl_mw) );
    io_InitTemp( &io_FB_SEK_Tvl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.fb_sek_tvl_mw) );
    io_InitTemp( &io_WW_HZG_Tvl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_hzg_tvl_mw) );
    io_InitTemp( &io_WW_HZG_Trl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_hzg_trl_mw) );
    io_InitTemp( &io_WW_Tww_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_tww_mw) );
}

/** \brief Methode zur Abfrage der Temperaturmessstellen.
  * Der Messwert wird in der Objektstruktur abgelegt und im Normalfall auch zurückgeben.
  * Bei unplausiblen Messwerten wird der rohe Messwert zurückgegeben und in der Objektstruktur
  * die jeweilige Messbereichsgrenze abgelegt, so dass noch sinnvoll weitergerechnet werden kann
  * \param self Pointer auf ein Temperaturmessobjekt
  */
io_obj_status_t io_Temp( io_temp_obj_t *self, float *mw )
{
    float temp_val;

    switch( self->status ) {
        case io_ManuelleZuweisung:
            if( (void *)mw != NULL )
                *mw = self->messwert;  
            /* Aus diesem Zustand kommt man nur durch Benutzerinteraktion (telnet.c) */
            break;
        case io_Normal:
            temp_val = TF(*(self->kbus_adresse_p));
            if( temp_val < IO_MIN_TEMP ) {
                self->status = io_Kurzschluss; 
                /* alten Messwert behalten */
            }
            else if( temp_val < self->messbereich_anfang ) {
                self->status = io_Unplausibel;
                self->messwert = self->messbereich_anfang; /* Messwert begrenzen */
            }
            else if( temp_val > IO_MAX_TEMP ) {
                self->status = io_Kabelbruch;
                /* alten Messwert behalten */
            }
            else if( temp_val > self->messbereich_ende ) {
                self->status = io_Unplausibel;
                self->messwert = self->messbereich_ende;   /* Messwert begrenzen */
            }
            else {
                /* Nur solange der Messwert in den Grenzen liegt bleibt der Zustand normal */
                self->status = io_Normal;  
                self->messwert = temp_val;
            }
            break;
        default:        
            temp_val = TF(*(self->kbus_adresse_p));
            if(    (temp_val >= self->messbereich_anfang)  
                && (temp_val <  self->messbereich_ende  ) ) {
                self->status = io_Normal;  /* Messwert liegt wieder in den normalen Grenzen */
                self->messwert = temp_val;
            }
            break;
    }
    
    if( (void *)mw != NULL )
        *mw = self->messwert;  /* Strukturwert in die Arbeitsvariable kopieren */
    return (self->status);
}

static
void io_InitY( io_ao10V_obj_t   *self, 
               float            stellbereich_anfang, 
               float            stellbereich_ende,
               io_obj_status_t  status,
               ao_0_10V_t       *kbus_adresse_p )
{
    self->stellbereich_anfang = stellbereich_anfang;
    self->stellbereich_ende   = stellbereich_ende;
    self->status              = io_Normal;
    self->kbus_adresse_p      = kbus_adresse_p;
}

void io_InitYAll( void )
{
    io_InitY( &io_KES_Tvl_Y,    MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.kes_tvl_y)    );
    io_InitY( &io_HK_MV_Y,      MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.hk_mv_y)      );
    io_InitY( &io_FB_PRIM_MV_Y, MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.fb_prim_mv_y) );
    io_InitY( &io_WW_HZG_MV_Y,  MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.ww_hzg_mv_y)  );
    io_InitY( &io_WW_HZG_PU_Y,  MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.ww_hzg_pu_y)  );
}

/** \brief Analogen Stellwert ausgeben mit Ueberprüfung auf Plausibilitaet.
  * \param self Pointer auf Ausgabeobjekt 
  * \param val Auszugebender Wert 
  * Der Stellwert wird auf der PLC ausgegeben und im Feld stellwert abgelegt.
  * Weiterhin wird geprueft, ob der gewuenschte Stellwert im plausiblen Bereich liegt.
  */
io_obj_status_t io_Y( io_ao10V_obj_t *self, float val )
{
    self->stellwert = val;
    if( val < self->stellbereich_anfang ) {
        *(self->kbus_adresse_p) = (self->stellbereich_anfang *AO_FULLSCALE)/100;
        self->status            = io_Unterlauf;
    }
    else if( val > self->stellbereich_ende ) {
        *(self->kbus_adresse_p) = (self->stellbereich_ende   *AO_FULLSCALE)/100;
        self->status            = io_Ueberlauf;
    }
    else { /* Angeforderter Stellwert im plausiblen Bereich */
        *(self->kbus_adresse_p) = (val*AO_FULLSCALE)/100;
        self->status            = io_Normal;
    }
    
    return(self->status);
}

/** \brief Alle IO´s (Temperaturen und 0-10V Ausgänge) initialisieren. 
  */
void io_Init( void )
{
    io_InitYAll();
    io_InitTempAll();
}

/** FBH, Partyschalter, DI, Taster   */
inline
u8_t io_get_ALL_PARTY( void )
{
    return (pabIn_p->din.all_party);
}

/** Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_SOL_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_pu_sb = sb;
    return (pabOut_p->dout.sol_pu_sb);
}

inline
di_bitbyte_t io_get_SOL_PU_SB( void )
{
    return (pabOut_p->dout.sol_pu_sb);
}

/** Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_SOL_SP1_AV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_sp1_av_sb = sb;
    return (pabOut_p->dout.sol_sp1_av_sb);
}

inline
di_bitbyte_t io_get_SOL_SP1_AV_SB( void )
{
    return (pabOut_p->dout.sol_sp1_av_sb);
}

/** Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_SOL_SP2_AV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_sp2_av_sb = sb;
    return (pabOut_p->dout.sol_sp2_av_sb);
}

inline
di_bitbyte_t io_get_SOL_SP2_AV_SB( void )
{
    return (pabOut_p->dout.sol_sp2_av_sb);
}

/** Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_KES_PU_SP1_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.kes_pu_sp1_sb = sb;
    return (pabOut_p->dout.kes_pu_sp1_sb);
}

inline
di_bitbyte_t io_get_KES_PU_SP1_SB( void )
{
    return (pabOut_p->dout.kes_pu_sp1_sb);
}

/** Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_KES_PU_SP2_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.kes_pu_sp2_sb = sb;
    return (pabOut_p->dout.kes_pu_sp2_sb);
}

inline
di_bitbyte_t io_get_KES_PU_SP2_SB( void )
{
    return (pabOut_p->dout.kes_pu_sp2_sb);
}

/** Heizkessel Sammelstoermeldung, DI, 24V */
inline
di_bitbyte_t io_get_KES_SSM( void )
{
    return (pabIn_p->din.kes_ssm);
}

/** Heizkessel Brennerbetriebsmeldung, DI, 24V */
inline
di_bitbyte_t io_get_KES_BR_BM( void )
{
    return (pabIn_p->din.kes_br_bm);
}

/** Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_HK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.hk_pu_sb = sb;
    return (pabOut_p->dout.hk_pu_sb);
}

inline
di_bitbyte_t io_get_HK_PU_SB( void )
{
    return (pabOut_p->dout.hk_pu_sb);
}

/** Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_FB_PRIM_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.fb_prim_pu_sb = sb;
    return (pabOut_p->dout.fb_prim_pu_sb);
}

inline
di_bitbyte_t io_get_FB_PRIM_PU_SB( void )
{
    return (pabOut_p->dout.fb_prim_pu_sb);
}

/** Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_FB_SEK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.fb_sek_pu_sb = sb;
    return (pabOut_p->dout.fb_sek_pu_sb);
}

inline
di_bitbyte_t io_get_FB_SEK_PU_SB( void )
{
    return (pabOut_p->dout.fb_sek_pu_sb);
}

/** Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
inline
di_bitbyte_t io_get_FB_SEK_TW( void )
{
    return (pabIn_p->din.fb_sek_tw);
}

/** Warmwasserzaehler, Zaehlereingang */
inline
u32_t io_get_WW_WZ_MW( void )
{
    // TODO:    return (pabIn_p->din.ww_wz_mw)
    return 9999;
}

/** Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
inline
di_bitbyte_t io_put_WW_HZG_VV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_hzg_vv_sb = sb;
    return (pabOut_p->dout.ww_hzg_vv_sb);
}

inline
di_bitbyte_t io_get_WW_HZG_VV_SB( void )
{
    return (pabOut_p->dout.ww_hzg_vv_sb);
}

/** Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
inline
di_bitbyte_t io_put_WW_HZG_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_hzg_pu_sb = sb;
    return (pabOut_p->dout.ww_hzg_pu_sb);
}

inline
di_bitbyte_t io_get_WW_HZG_PU_SB( void )
{
    return (pabOut_p->dout.ww_hzg_pu_sb);
}

/** Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
inline
di_bitbyte_t io_put_WW_ZIRK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_zirk_pu_sb = sb;
    return (pabOut_p->dout.ww_zirk_pu_sb);
}

inline
di_bitbyte_t io_get_WW_ZIRK_PU_SB( void )
{
    return (pabOut_p->dout.ww_zirk_pu_sb);
}

/** Warmwasser, Partyschalter, DI, Taster  */
inline
di_bitbyte_t io_get_WW_PARTY( void )
{
    return (pabIn_p->din.ww_party);
}

/** Gesamtstörmeldung */
inline
di_bitbyte_t io_put_STOERUNG( do_bitbyte_t sb )
{
    pabOut_p->dout.stoerung = sb;
    return (pabOut_p->dout.stoerung);
}

inline
di_bitbyte_t io_get_STOERUNG( void )
{
    return (pabOut_p->dout.stoerung);
}

/** Ausgang Steuerung aktiv */
inline
di_bitbyte_t io_put_CONTROL_AKTIV( do_bitbyte_t sb )
{
    pabOut_p->dout.control_aktiv = sb;
    return (pabOut_p->dout.control_aktiv);
}

inline
di_bitbyte_t io_get_CONTROL_AKTIV( void )
{
    return (pabOut_p->dout.control_aktiv);
}

