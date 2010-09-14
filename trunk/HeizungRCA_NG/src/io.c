#define _IO_C_

#include "gen_types.h"
#include "io.h"

/** Aussentemperatur, AI, Pt1000     */
inline float io_get_ALL_Tau_MW( void )
{
    return TF(pabIn_p->ain.all_tau_mw);             
}

/** FBH, Partyschalter, DI, Taster   */
inline u8_t io_get_ALL_PARTY( void )
{
    return (pabIn_p->din.all_party);                
}

/** Kollektortemperatur, AI, Pt1000  */
inline float io_get_SOL_KOLL_T_MW( void )   
{
    return TF(pabIn_p->ain.sol_koll_t_mw);          
}    

/** Temperatur im Speicher 1 unten, AI, Pt1000 */
inline float io_get_SOL_SP1_Tu_MW( void )
{
    return TF(pabIn_p->ain.sol_sp1_tu_mw);          
}

/** Temperatur im Speicher 1 oben, AI, Pt1000  */
inline float io_get_SOL_SP1_To_MW( void )
{
    return TF(pabIn_p->ain.sol_sp1_to_mw);          
}

/** Temperatur im Speicher 2 unten, AI, Pt1000 */
inline float io_get_SOL_SP2_Tu_MW( void )
{
    return TF(pabIn_p->ain.sol_sp2_tu_mw);          
}

/** Temperatur im Speicher 2 oben, AI, Pt1000  */
inline float io_get_SOL_SP2_To_MW( void )
{
   return TF(pabIn_p->ain.sol_sp2_to_mw);           
}

/** Solarkreislaufpumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_SOL_PU_SB( do_bitbyte_t sb ) 
{
    pabOut_p->dout.sol_pu_sb = sb;                  
    return (pabOut_p->dout.sol_pu_sb);
}

/** Solar-Absperrventil, Speicher 1 (auf/zu), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_SOL_SP1_AV_SB( do_bitbyte_t sb ) 
{
    pabOut_p->dout.sol_sp1_av_sb = sb;              
    return (pabOut_p->dout.sol_sp1_av_sb);
}

/** Solar-Absperrventil, Speicher 2 (auf/zu), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_SOL_SP2_AV_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.sol_sp2_av_sb = sb;              
    return (pabOut_p->dout.sol_sp2_av_sb);
}

/** Kesselvorlauftemperatur, AI, Pt1000   */
inline float io_get_KES_Tvl_MW( void )
{
    return TF(pabIn_p->ain.kes_tvl_mw);             
}

/** Kesselruecklauftemperatur, AI, Pt1000 */
inline float io_get_KES_Trl_MW( void )
{
    return TF(pabIn_p->ain.kes_trl_mw);             
}

/** Kesselvorlauftemperaturvorgabe, AO, 0-10V */    
inline void io_put_KES_Tvl_Y( float pct ) 
{      
    pabOut_p->aout.kes_tvl_y = (pct*AO_FULLSCALE)/100;    
}

/** Ladepumpe fuer Speicher 1 (ein, aus), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_KES_PU_SP1_SB( do_bitbyte_t sb ) 
{
    pabOut_p->dout.kes_pu_sp1_sb = sb;              
    return (pabOut_p->dout.kes_pu_sp1_sb);
}

/** Ladepumpe fuer Speicher 2 (ein, aus), DO, 24V Ausgang auf Relais */    
inline di_bitbyte_t io_put_KES_PU_SP2_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.kes_pu_sp2_sb = sb;              
    return (pabOut_p->dout.kes_pu_sp2_sb);
}

/** Heizkessel Sammelstoermeldung, DI, 24V */
inline di_bitbyte_t io_get_KES_SSM( void )  
{
    return (pabIn_p->din.kes_ssm);          
}

/** Heizkessel Brennerbetriebsmeldung, DI, 24V */
inline di_bitbyte_t io_get_KES_BR_BM( void )
{
    return (pabIn_p->din.kes_br_bm); 
}

/** Heizkoerper-Heizkreis Vorlauftemperatur, AI, Pt1000 */    
inline float io_get_HK_Tvl_MW( void )
{
    return TF(pabIn_p->ain.hk_tvl_mw);
}
    
/** Heizkoerper-Heizkreis Ruecklauftemperatur, AI, Pt1000 */
inline float io_get_HK_Trl_MW( void )
{
    return TF(pabIn_p->ain.hk_trl_mw);
}

/** Heizkoerper-Heizkreis Mischventil-Ansteuerung, AO, 0-10V */
inline void io_put_HK_MV_Y( float pct ) 
{
    pabOut_p->aout.hk_mv_y = (pct*AO_FULLSCALE)/100;    
}

/** Heizkoerper-Heizkreis Pumpe (ein/aus), DO, 24V Ausgang auf Relais */    
inline di_bitbyte_t io_put_HK_PU_SB( do_bitbyte_t sb )  
{
    pabOut_p->dout.hk_pu_sb = sb;
    return (pabOut_p->dout.hk_pu_sb);
}

/** Fussbodenheizung, Primaerseite, Ruecklauftemperatur, AI, Pt1000 */
inline float io_get_FB_PRIM_Trl_MW( void )  
{
    return TF(pabIn_p->ain.fb_prim_trl_mw);
}

/** Fussbodenheizung, Sekundaerseite, Vorlauftemperatur, AI, Pt1000 */
inline float io_get_FB_SEK_Tvl_MW( void )
{
    return TF(pabIn_p->ain.fb_sek_tvl_mw);
}   

/** Fussbodenheizung, Primaerseite, Mischerventilansteuerung, AO, 0-10V */
inline void io_put_FB_PRIM_MV_Y( float pct ) 
{
    pabOut_p->aout.fb_prim_mv_y = (pct*AO_FULLSCALE)/100; 
}

/** Fussbodenheizung, Primaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_FB_PRIM_PU_SB( do_bitbyte_t sb ) 
{
    pabOut_p->dout.fb_prim_pu_sb = sb;
    return (pabOut_p->dout.fb_prim_pu_sb);
}

/** Fussbodenheizung, Sekundaerseite, Pumpe (ein/aus), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_FB_SEK_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.fb_sek_pu_sb = sb;
    return (pabOut_p->dout.fb_sek_pu_sb);
}

/** Fussbodenheizung, Sicherheitstemperaturwaechter, DI, 24V */
inline di_bitbyte_t io_get_FB_SEK_TW( void ) 
{
    return (pabIn_p->din.fb_sek_tw);
}

/** Warmwasser, Heizungsvorlauftemperatur, AI, Pt1000 */
inline float io_get_WW_HZG_Tvl_MW( void )
{
    return TF(pabIn_p->ain.ww_hzg_tvl_mw);
}

/** Warmwasser, Heizungsruecklauftemperatur, AI, Pt1000 */
inline float io_get_WW_HZG_Trl_MW( void )
{
    return TF(pabIn_p->ain.ww_hzg_trl_mw);
}

/** Warmwasser-Temperatur, AI, Pt1000 */
inline float io_get_WW_Tww_MW( void )
{
    return TF(pabIn_p->ain.ww_tww_mw);
}   

/** Warmwasserzaehler, Zaehlereingang */
inline u32_t io_get_WW_WZ_MW( void )
{
    // TODO:    return (pabIn_p->din.ww_wz_mw)         
    return 9999;
}

/** Warmwasser, Heizungsmischventil, Vorlauf, AO, 0-10V */
inline void io_put_WW_HZG_MV_Y( float pct )
{
    pabOut_p->aout.ww_hzg_mv_y = (pct*AO_FULLSCALE)/100; 
}

/** Warmwasser, Heizungsverteilventil, Ruecklauf, (auf/zu), DO, 24V Ausgang auf Relais */
inline di_bitbyte_t io_put_WW_HZG_VV_SB( do_bitbyte_t sb )  
{
    pabOut_p->dout.ww_hzg_vv_sb = sb;
    return (pabOut_p->dout.ww_hzg_vv_sb);
}

/** Warmwasser, Heizungspumpe, (ein/aus), D0, 24 Ausgang auf Relais */
inline di_bitbyte_t io_put_WW_HZG_PU_SB( do_bitbyte_t sb )
{
    pabOut_p->dout.ww_hzg_pu_sb = sb;
    return (pabOut_p->dout.ww_hzg_pu_sb);   
}

/** Warmwasser, Heizungspumpe, Leistung, A0, 0-10V */
inline void io_put_WW_HZG_PU_Y( float pct )
{
    pabOut_p->aout.ww_hzg_pu_y = (pct*AO_FULLSCALE)/100; 
}

/** Warmwasser, Zirkulationspumpe, (ein/aus), D0, 24 Ausgang auf Relais */    
inline di_bitbyte_t io_put_WW_ZIRK_PU_SB( do_bitbyte_t sb ) 
{
    pabOut_p->dout.ww_zirk_pu_sb = sb;
    return (pabOut_p->dout.ww_zirk_pu_sb);
}

/** Warmwasser, Partyschalter, DI, Taster  */
inline di_bitbyte_t io_get_WW_PARTY( void )     
{
    return (pabIn_p->din.ww_party);         
}

/** Gesamtstörmeldung */
inline di_bitbyte_t io_put_STOERUNG( do_bitbyte_t sb ) 
{
    pabOut_p->dout.stoerung = sb;
    return (pabOut_p->dout.stoerung);
}

/** Ausgang Steuerung aktiv */    
inline di_bitbyte_t io_put_CONTROL_AKTIV( do_bitbyte_t sb )  
{
    pabOut_p->dout.control_aktiv = sb;
    return (pabOut_p->dout.control_aktiv);
}

