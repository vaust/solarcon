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
#include "err.h"

typedef struct enable_modul_s {
    u16_t sol_aktiv       : 1;  /**< Statusbit Solarkollektor aktiv             */
    u16_t fb_aktiv        : 1;  /**< Statusbit Fussbodenheizung aktiv           */
    u16_t hk_aktiv        : 1;  /**< Statusbit Heizkoerperheizkreis aktiv       */
    u16_t ww_aktiv        : 1;  /**< Statusbit Warmwassersteuerung aktiv        */
    u16_t kes_aktiv       : 1;  /**< Statusbit Kesselsteuerung aktiv            */
    u16_t err_aktiv       : 1;  /**< Statusbit Sammelstoermeldung aktiv         */
    u16_t inp_sol_aktiv   : 1;  /**< Statusbit Solar-Eingabe aktiv              */
    u16_t inp_fb_aktiv    : 1;  /**< Statusbit Fussbodenheizung-Eingabe aktiv   */
    u16_t inp_hk_aktiv    : 1;  /**< Statusbit Heizkoerper-Eingabe aktiv        */
    u16_t inp_ww_aktiv    : 1;  /**< Statusbit Warmwasser-Eingabe aktiv         */
    u16_t inp_kes_aktiv   : 1;  /**< Statusbit Kessel-Eingabe aktiv             */
    u16_t inp_err_aktiv   : 1;  /**< Statusbit Sammelstoermeldung Eingabe aktiv */
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

/* Stoermeldung */
PUBLIC err_param_t         cntrl_err_par;
PUBLIC err_in_t            cntrl_err_in;
PUBLIC err_out_t           cntrl_err_out;

/* --DEBUG Variablen -- */
PUBLIC u16_t    cntrl_cnt;
PUBLIC s16_t    cntrl_DEBUG01;

/* globales Schedulerwarteflag */
PUBLIC u8_t     cntrl_TaskFlag;

/* Prototypen */
void cntrl_open( void );
void cntrl_run( int sig );
void cntrl_close( void );
void *cntrl_Task( void *arg );
void cntrl_SetTaskFlag( void );

#endif /* _CNTRL_H_ */

