#ifndef _TELNET_VARS_H_
#define _TELNET_VARS_H_

#ifdef _TELNET_C_
static const parse_set_t telnet_fb_Vars[] =
{
    { "fb.reg.p.kp",           &(cntrl_fb.reg.p.kp),           "%f" },
    { "fb.reg.p.ki",           &(cntrl_fb.reg.p.ki),           "%f" },
    { "fb.reg.p.ap",           &(cntrl_fb.reg.p.ap),           "%f" },
    { "fb.reg.p.TA",           &(cntrl_fb.reg.p.TA),           "%f" },
    { "fb.reg.p.lower_limit",  &(cntrl_fb.reg.p.lower_limit),  "%f" },
    { "fb.reg.p.upper_limit",  &(cntrl_fb.reg.p.upper_limit),  "%f" },

    { "fb.p.tvl_absenk",       &(cntrl_fb.p.tvl_absenk),       "%f" },
    { "fb.p.tvl_steigung",     &(cntrl_fb.p.tvl_steigung),     "%f" },
    { "fb.p.tvl_niveau",       &(cntrl_fb.p.tvl_niveau),       "%f" },
    { "fb.p.tvl_min",          &(cntrl_fb.p.tvl_min),          "%f" },
    { "fb.p.tvl_max",          &(cntrl_fb.p.tvl_max),          "%f" },
    { "fb.p.at_start",         &(cntrl_fb.p.at_start),         "%f" },
    { "fb.p.frostschutz",      &(cntrl_fb.p.frostschutz),      "%f" },
    { "fb.p.tr_sw",            &(cntrl_fb.p.tr_sw),            "%f" },

    { "fb.i.tau_mw",           &(cntrl_fb.i.tau_mw),           "%f" },
    { "fb.i.sek_tvl_mw",       &(cntrl_fb.i.sek_tvl_mw),       "%f" },
    { "fb.i.zustand",          &(cntrl_fb.i.zustand),          "%x" },
    { "fb.i.partytime_flg",    &(cntrl_fb.i.partytime_flg),    "%x" },

    { "fb.o.tvl_sw",           &(cntrl_fb.o.tvl_sw),           "%f" },
    { "fb.o.prim_mv_y",        &(cntrl_fb.o.prim_mv_y),        "%f" },
    { "fb.reg.x[0]",           &(cntrl_fb.reg.x[0]),           "%f" },
    { "fb.reg.x[1]",           &(cntrl_fb.reg.x[1]),           "%f" },
    { "fb.reg.x[2]",           &(cntrl_fb.reg.x[2]),           "%f" },
    { "fb.reg.x[3]",           &(cntrl_fb.reg.x[3]),           "%f" },
    { "fb.o.prim_pu_sb",       &(cntrl_fb.o.prim_pu_sb),       "%x" },
    { "fb.o.sek_pu_sb",        &(cntrl_fb.o.sek_pu_sb),        "%x" },
};

static const parse_set_t telnet_hk_Vars[] =
{
    { "hk.reg.p.kp",           &(cntrl_hk.reg.p.kp),           "%f" },
    { "hk.reg.p.ki",           &(cntrl_hk.reg.p.ki),           "%f" },
    { "hk.reg.p.ap",           &(cntrl_hk.reg.p.ap),           "%f" },
    { "hk.reg.p.TA",           &(cntrl_hk.reg.p.TA),           "%f" },
    { "hk.reg.p.lower_limit",  &(cntrl_hk.reg.p.lower_limit),  "%f" },
    { "hk.reg.p.upper_limit",  &(cntrl_hk.reg.p.upper_limit),  "%f" },

    { "hk.p.tvl_absenk",       &(cntrl_hk.p.tvl_absenk),       "%f" },
    { "hk.p.tvl_steigung",     &(cntrl_hk.p.tvl_steigung),     "%f" },
    { "hk.p.tvl_niveau",       &(cntrl_hk.p.tvl_niveau),       "%f" },
    { "hk.p.tvl_min",          &(cntrl_hk.p.tvl_min),          "%f" },
    { "hk.p.tvl_max",          &(cntrl_hk.p.tvl_max),          "%f" },
    { "hk.p.at_start",         &(cntrl_hk.p.at_start),         "%f" },
    { "hk.p.frostschutz",      &(cntrl_hk.p.frostschutz),      "%f" },
    { "hk.p.tr_sw",            &(cntrl_hk.p.tr_sw),            "%f" },

    { "hk.i.tau_mw",           &(cntrl_hk.i.tau_mw),           "%f" },
    { "hk.i.tau_avg",          &(cntrl_hk.i.tau_avg),          "%f" },
    { "hk.i.tvl_mw",           &(cntrl_hk.i.tvl_mw),           "%f" },
    { "hk.i.zustand",          &(cntrl_hk.i.zustand),          "%x" },
    { "hk.i.partytime_flg",    &(cntrl_hk.i.partytime_flg),    "%x" },

    { "hk.o.tvl_sw",           &(cntrl_hk.o.tvl_sw),           "%f" },
    { "hk.o.mv_y",             &(cntrl_hk.o.mv_y),             "%f" },
    { "hk_.reg.x[0]",          &(cntrl_hk.reg.x[0]),           "%f" },
    { "hk_.reg.x[1]",          &(cntrl_hk.reg.x[1]),           "%f" },
    { "hk_.reg.x[2]",          &(cntrl_hk.reg.x[2]),           "%f" },
    { "hk_.reg.x[3]",          &(cntrl_hk.reg.x[3]),           "%f" },
    { "hk_out.pu_sb",          &(cntrl_hk.o.pu_sb),            "%x" },
};

static const parse_set_t telnet_ww_Vars[] =
{
    { "ww_par.pu_reg_kp",           &(cntrl_ww_par.pu_reg_kp),           "%f" },
    { "ww_par.pu_reg_ki",           &(cntrl_ww_par.pu_reg_ki),           "%f" },
    { "ww_par.pu_reg_ap",           &(cntrl_ww_par.pu_reg_ap),           "%f" },
    { "ww_par.TA",                  &(cntrl_ww_par.TA),                  "%f" },
    { "ww_par.kes_sp_dt_sw",        &(cntrl_ww_par.kes_sp_dt_sw),        "%f" },
    { "ww_par.tww_sw",              &(cntrl_ww_par.tww_sw),              "%f" },
    { "ww_par.frostschutz",         &(cntrl_ww_par.frostschutz),         "%f" },
    { "ww_par.at_start",            &(cntrl_ww_par.at_start),            "%f" },
    { "ww_par.mv_korr",             &(cntrl_ww_par.mv_korr),             "%f" },
    { "ww_par.hzg_pu_y_min",        &(cntrl_ww_par.hzg_pu_y_min),        "%f" },
    { "ww_par.schwachlastzeit_max", &(cntrl_ww_par.schwachlastzeit_max), "%d" },

    { "ww_in.tww_mw",          &(cntrl_ww_in.tww_mw),          "%f" },
    { "ww_in.tau_mw",          &(cntrl_ww_in.tau_mw),          "%f" },
    { "ww_in.tau_avg",         &(cntrl_ww_in.tau_avg),         "%f" },
    { "ww_in.hzg_tvl_mw",      &(cntrl_ww_in.hzg_tvl_mw),      "%f" },
    { "ww_in.hzg_trl_mw",      &(cntrl_ww_in.hzg_trl_mw),      "%f" },
    { "ww_in.hk_tvl_sw",       &(cntrl_ww_in.hk_tvl_sw),       "%f" },
    { "ww_in.sp1_to_mw",       &(cntrl_ww_in.sp1_to_mw),       "%f" },
    { "ww_in.sp2_tu_mw",       &(cntrl_ww_in.sp2_tu_mw),       "%f" },
    { "ww_in.zirkzustand",     &(cntrl_ww_in.zirkzustand),     "%x" },

    { "ww_out.hzg_tvl_sw",     &(cntrl_ww_out.hzg_tvl_sw),     "%f" },
    { "ww_out.hzg_mv_y.y",     &(cntrl_ww_out.hzg_mv_y.y),     "%f" },
    { "ww_out.hzg_pu_y.y",     &(cntrl_ww_out.hzg_pu_y.y),     "%f" },
    { "ww_out.hzg_pu_y.x[0]",  &(cntrl_ww_out.hzg_pu_y.x[0]),  "%f" },
    { "ww_out.hzg_pu_y.x[1]",  &(cntrl_ww_out.hzg_pu_y.x[1]),  "%f" },
    { "ww_out.hzg_pu_y.x[2]",  &(cntrl_ww_out.hzg_pu_y.x[2]),  "%f" },
    { "ww_out.hzg_pu_y.x[3]",  &(cntrl_ww_out.hzg_pu_y.x[3]),  "%f" },
    { "ww_out.hzg_pu_sb",      &(cntrl_ww_out.hzg_pu_sb),      "%x" },
    { "ww_out.hzg_vv_sb",      &(cntrl_ww_out.hzg_vv_sb),      "%x" },

    { "ww_q.TA",               &(cntrl_ww_q.TA),               "%f" },
    { "ww_q.kp",               &(cntrl_ww_q.kp),               "%f" },
    { "ww_q.ki",               &(cntrl_ww_q.ki),               "%f" },
    { "ww_q.ap",               &(cntrl_ww_q.ap),               "%f" },
    { "ww_q.lower_limit",      &(cntrl_ww_q.lower_limit),      "%f" },
    { "ww_q.upper_limit",      &(cntrl_ww_q.upper_limit),      "%f" }
};

static const parse_set_t telnet_sol_Vars[] =
{
    { "sol_par.sp_t_max",       &(cntrl_sol_par.sp_t_max),       "%f" },
    { "sol_par.dt_ein_sw",      &(cntrl_sol_par.dt_ein_sw),      "%f" },
    { "sol_par.dt_aus_sw",      &(cntrl_sol_par.dt_aus_sw),      "%f" },

    { "sol_in.koll_t_mw[KO1]",  &(cntrl_sol_in.koll_t_mw[KO1]),  "%f" },
    { "sol_in.t_sp[SP1].to_mw", &(cntrl_sol_in.t_sp[SP1].to_mw), "%f" },
    { "sol_in.t_sp[SP1].tu_mw", &(cntrl_sol_in.t_sp[SP1].tu_mw), "%f" },
    { "sol_in.t_sp[SP2].to_mw", &(cntrl_sol_in.t_sp[SP2].to_mw), "%f" },
    { "sol_in.t_sp[SP2].tu_mw", &(cntrl_sol_in.t_sp[SP2].tu_mw), "%f" },

    { "sol_out.av_sb[SP1]",     &(cntrl_sol_out.av_sb[SP1]),     "%x" },
    { "sol_out.av_sb[SP2]",     &(cntrl_sol_out.av_sb[SP2]),     "%x" },
    { "sol_out.pu_sb[KO1]",     &(cntrl_sol_out.pu_sb[SP1]),     "%x" }
};

static const parse_set_t telnet_kes_Vars[] =
{
    { "kes_par.sp_dt_sw",     &(cntrl_kes_par.sp_dt_sw),     "%f" },
    { "kes_par.ww_tww_sw",    &(cntrl_kes_par.ww_tww_sw),    "%f" },

    { "kes_in.sp1_to_mw",     &(cntrl_kes_in.sp1_to_mw),     "%f" },
    { "kes_in.sp2_to_mw",     &(cntrl_kes_in.sp2_to_mw),     "%f" },
    { "kes_in.tvl_mw",        &(cntrl_kes_in.tvl_mw),        "%f" },
    { "kes_in.hk_tvl_sw",     &(cntrl_kes_in.hk_tvl_sw),     "%f" },
    { "kes_in.fb_tvl_sw",     &(cntrl_kes_in.fb_tvl_sw),     "%f" },
    { "kes_in.fb_prim_mv_y",  &(cntrl_kes_in.fb_prim_mv_y),  "%f" },
    { "kes_in.duschzeit",     &(cntrl_kes_in.duschzeit),     "%x" },
    { "kes_in.br_bm",         &(cntrl_kes_in.br_bm),         "%x" },

    { "kes_out.sp1_to_sw",    &(cntrl_kes_out.sp1_to_sw),    "%f" },
    { "kes_out.sp2_to_sw",    &(cntrl_kes_out.sp2_to_sw),    "%f" },
    { "kes_out.tvl_sw_sp1",   &(cntrl_kes_out.tvl_sw_sp1),   "%f" },
    { "kes_out.tvl_sw_sp2",   &(cntrl_kes_out.tvl_sw_sp2),   "%f" },
    { "kes_out.tvl_sw",       &(cntrl_kes_out.tvl_sw),       "%f" },
    { "kes_out.pu_sp1_sb",    &(cntrl_kes_out.pu_sp1_sb),    "%x" },
    { "kes_out.pu_sp2_sb",    &(cntrl_kes_out.pu_sp2_sb),    "%x" }
};

static const parse_set_t telnet_err_Vars[] =
{
    { "err_par.br_TimeOut",           &(cntrl_err_par.br_TimeOut),           "%d" },
    { "err_par.dt",                   &(cntrl_err_par.dt),                   "%f" },

    { "err_in.kes_tvl_sw",            &(cntrl_err_in.kes_tvl_sw),            "%f" },
    { "err_in.kes_tvl_mw",            &(cntrl_err_in.kes_tvl_mw),            "%f" },
    { "err_in.br_RueckMeldung",       &(cntrl_err_in.br_RueckMeldung),       "%x" },
    { "err_in.br_StoerMeldung",       &(cntrl_err_in.br_StoerMeldung),       "%x" },
    { "err_in.stb_Fussbodenheizung",  &(cntrl_err_in.stb_Fussbodenheizung),  "%x" },
    { "err_in.tempsens_errcnt",       &(cntrl_err_in.tempsens_errcnt),       "%d" },
    { "err_in.sol_errcnt",            &(cntrl_err_in.sol_errcnt),            "%d" },
    { "err_in.ao_errcnt",             &(cntrl_err_in.ao_errcnt),             "%d" },
    { "err_in.common_errcnt",         &(cntrl_err_in.common_errcnt),         "%d" },
    
    { "err_out.br_Countdown",         &(cntrl_err_out.br_Countdown),         "%d" },
    { "err_out.Sammelstoermeldung",   &(cntrl_err_out.Sammelstoermeldung),   "%x" }
};

static const char *telnet_help_text[] =
{
    "\nMögliche Befehle: \n\n",

    "\tGET T        : alle Temperaturmesswerte\n",
    "\tGET SW       : alle Sollwerte\n",
    "\tGET AO       : alle Analog-Ausgaenge\n",
    "\tGET DI       : alle Digital-Eingaenge\n",
    "\tGET DO       : alle Digital-Ausgaenge\n",
    "\tGET FB       : Daten zur FB-Heizung\n",
    "\tGET WW       : Daten zu Warmwasserbereitung\n",
    "\tGET SOL      : Daten zu Solarbeheizung\n",
    "\tGET HK       : Daten zu Heizkoerper-Heizkreis\n",
    "\tGET PAR      : Eingelesene Parameter ausgeben\n",
    "\tGET ZEIT     : Eingelesenes Zeitprogramm ausgeben\n",
    "\tGET NOW      : akt. Steuerungszeit aus localtime() ausgeben (nicht Linux Zeit !!)\n",
    "\tGET ABS      : Absenkungen ausgeben\n",
    "\tGET VFB <n>  : FB Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\tGET VHK <n>  : HK Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\tGET VWW <n>  : WW Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\tGET VSOL <n> : SOL Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\tGET VKES <n> : KES Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\tGET VERR <n> : ERR Modul: Parameter-, Eingangs- und Ausgangsvariablen\n",
    "\t               <n> Nummer der Variablen oder -1 für komplette Liste\n\n",

    "\tPUT V<mdl> <var-nr> <=| > <wert> \n",
    "\t             : Modul Variable manuell setzen\n",
    "\t               Beispiel: put vww 23 0.0 \n",
    "\t               Ausgangsgroessen sind nur im Handbetrieb aenderbar.\n",
    "\t               <var-nr> ergibt sich aus Ausgabe von GET Vxxx -1\n\n",

    "\tAUTO <mdl>   : Modul SOL, FB, HK, WW, KES, ERR auf Automatik\n",
    "\tAUTO IN<mdl> : Prozesseingabe SOL, FB, HK, WW, KES, ERR auf Automatik\n",
    "\tAUTO ALL     : alle Prozesseingaben und Module auf Automatik\n",
    "\tHAND <mdl>   : Modul SOL, FB, HK, WW, KES, ERR auf Handbetrieb\n",
    "\tHAND IN<mdl> : Prozesseingabe SOL, FB, HK, WW, KES, ERR auf Handbetrieb\n",
    "\tMODUL        : Anzeige aller Module incl. Betriebszustand\n",

    "\tINIT         : Initialisierungsdateien neu einlesen\n",
    "\tENTSTOEREN   : Sammelstoermeldung zuruecksetzen\n\n",

    "\tHELP         : Diesen Hilfetext ausgeben\n",
    "\tVERSION      : Software Version ausgeben\n",
    "\tEND          : Datenabfrage beenden\n\n"
};

static const parse_set_t telnet_dbg_Vars[] =
{
    { "cntrl_cnt",          &cntrl_cnt,          "%ld" },
    { "cntrl_TaskFlag_cnt", &cntrl_TaskFlag_cnt, "%d" },
    { "Debug",              &Debug,              "%d" },
};

static const char *telnet_wochentage[] =
{
    "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"
};

#else
#error "Header nicht von telnet.c eingebunden"
#endif // _TELNET_C_
#endif // _TELNET_VARS_H_



