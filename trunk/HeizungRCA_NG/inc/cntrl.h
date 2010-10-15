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


typedef enable_modul_s {
    u8_t sol_aktiv  : 1;
    u8_t fb_aktiv   : 1;
    u8_t hk_aktiv   : 1;
    u8_t ww_aktiv   : 1;
    u8_t kes_aktiv  : 1;
    u8_t            : 3;
} enable_modul_t;

/* <Globals> Sichtbar in cntrl.c und telnet.c */
#undef PUBLIC
#ifdef _CNTRL_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

PUBLIC enable_modul_t   cntrl_mdl_aktiv;

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

#endif

