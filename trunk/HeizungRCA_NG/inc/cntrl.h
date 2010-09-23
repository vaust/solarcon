#ifndef _CNTRL_H_
#define _CNTRL_H_

#include "sup.h"
#include "gen_types.h"

#include "zeit.h"
#include "task.h"
#include "sol.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "kes.h"

/* <Globals> Sichtbar in cntrl.c und telnet.c */
#undef PUBLIC
#ifdef _CNTRL_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/* Variablen fuer Zeit */
PUBLIC zeit_Betriebszustand_t  cntrl_zeit_absenkung;
PUBLIC zeit_event_t            cntrl_zeit_event;
PUBLIC zeit_party_t            cntrl_zeit_party;

/* Mittelwertbildung fuer Aussentemperatur */
PUBLIC task_tau_t   cntrl_tau;

/* Variablen fuer Solarkollektorsteuerung */
PUBLIC sol_param_t  cntrl_sol_par;
PUBLIC sol_in_t     cntrl_sol_in;
PUBLIC sol_out_t    cntrl_sol_out;

/* Variablen fuer Fussbodenheizung */
PUBLIC fb_param_t          cntrl_fb_par;
PUBLIC fb_in_t             cntrl_fb_in;
PUBLIC fb_out_t            cntrl_fb_out;
PUBLIC sup_digreg_coeff_t  cntrl_fb_q;

/* Variablen fuer Heizkoerperkreis */
PUBLIC hk_param_t          cntrl_hk_par;
PUBLIC hk_in_t             cntrl_hk_in;
PUBLIC hk_out_t            cntrl_hk_out;
PUBLIC sup_digreg_coeff_t  cntrl_hk_q;

/* Variablen fuer Warmwasserkreis  */
PUBLIC ww_param_t          cntrl_ww_par;
PUBLIC ww_in_t             cntrl_ww_in;
PUBLIC ww_out_t            cntrl_ww_out;
PUBLIC sup_digreg_coeff_t  cntrl_ww_q;

/* Variablen fuer Kessel Steuerung */
PUBLIC kes_param_t         cntrl_kes_par; 
PUBLIC kes_in_t            cntrl_kes_in;
PUBLIC kes_out_t           cntrl_kes_out;

#ifdef _TELNET_C_
/* Variablennamen -> Mapping */
{
    { "fb_par.reg_kp",         &(cntrl_fb_par.reg_kp),         "%f" }, 
    { "fb_par.reg_tn",         &(cntrl_fb_par.reg_tn),         "%f" },
    { "fb_par.TA",             &(cntrl_fb_par.TA),             "%f" },
    { "fb_par.tvl_absenk",     &(cntrl_fb_par.tvl_absenk),     "%f" },
    { "fb_par.tvl_steigung",   &(cntrl_fb_par.tvl_steigung),   "%f" },
    { "fb_par.tvl_niveau",     &(cntrl_fb_par.tvl_niveau),     "%f" },
    { "fb_par.tvl_min",        &(cntrl_fb_par.tvl_min),        "%f" },
    { "fb_par.tvl_max",        &(cntrl_fb_par.tvl_max),        "%f" },
    { "fb_par.at_start",       &(cntrl_fb_par.at_start),       "%f" },
    { "fb_par.frostschutz",    &(cntrl_fb_par.frostschutz),    "%f" },
    { "fb_par.float tr_sw",    &(cntrl_fb_par.float tr_sw),    "%f" },

    { "fb_in.tau_mw",          &(cntrl_fb_in.tau_mw),          "%f" },
    { "fb_in.tau_avg",         &(cntrl_fb_in.tau_avg),         "%f" },
    { "fb_in.sek_tvl_mw",      &(cntrl_fb_in.sek_tvl_mw),      "%f" },
    { "fb_in.zustand",         &(cntrl_fb_in.zustand),         "%d" },
    { "fb_in.partytime_flg",   &(cntrl_fb_in.partytime_flg),   "%d" },
     
    { "fb_out.tvl_sw",         &(cntrl_fb_out.tvl_sw),         "%f" },
    { "fb_out.prim_mv_y.y",    &(cntrl_fb_out.prim_mv_y.y),    "%f" },
    { "fb_out.prim_mv_y.y_1",  &(cntrl_fb_out.prim_mv_y.y_1),  "%f" },
    { "fb_out.prim_mv_y.xd_1", &(cntrl_fb_out.prim_mv_y.xd_1), "%f" },
    { "fb_out.prim_pu_sb",     &(cntrl_fb_out.prim_pu_sb),     "%d" },
    { "fb_out.sek_pu_sb",      &(cntrl_fb_out.sek_pu_sb),      "%d" }
}
/* <Globals/> */
#endif

