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
    { "hk.reg.x[0]",           &(cntrl_hk.reg.x[0]),           "%f" },
    { "hk.reg.x[1]",           &(cntrl_hk.reg.x[1]),           "%f" },
    { "hk.reg.x[2]",           &(cntrl_hk.reg.x[2]),           "%f" },
    { "hk.reg.x[3]",           &(cntrl_hk.reg.x[3]),           "%f" },
    { "hk.o.pu_sb",            &(cntrl_hk.o.pu_sb),            "%x" },
};

static const parse_set_t telnet_ww_Vars[] =
{
    { "ww.reg_pu.p.kp",           &(cntrl_ww.reg_pu.p.kp),           "%f" },
    { "ww.reg_pu.p.ki",           &(cntrl_ww.reg_pu.p.ki),           "%f" },
    { "ww.reg_pu.p.ap",           &(cntrl_ww.reg_pu.p.ap),           "%f" },
    { "ww.reg_pu.p.TA",           &(cntrl_ww.reg_pu.p.TA),           "%f" },
    { "ww.reg_pu.p.lower_limit",  &(cntrl_ww.reg_pu.p.lower_limit),  "%f" },
    { "ww.reg_pu.p.upper_limit",  &(cntrl_ww.reg_pu.p.upper_limit),  "%f" },

    { "ww.p.kes_sp_dt_sw",        &(cntrl_ww.p.kes_sp_dt_sw),        "%f" },
    { "ww.p.tww_sw",              &(cntrl_ww.p.tww_sw),              "%f" },
    { "ww.p.frostschutz",         &(cntrl_ww.p.frostschutz),         "%f" },
    { "ww.p.at_start",            &(cntrl_ww.p.at_start),            "%f" },
    { "ww.p.mv_korr",             &(cntrl_ww.p.mv_korr),             "%f" },
    { "ww.p.hzg_pu_y_min",        &(cntrl_ww.p.hzg_pu_y_min),        "%f" },
    { "ww.p.schwachlastzeit_max", &(cntrl_ww.p.schwachlastzeit_max), "%d" },

    { "ww.i.tww_mw",              &(cntrl_ww.i.tww_mw),              "%f" },
    { "ww.i.tau_mw",              &(cntrl_ww.i.tau_mw),              "%f" },
    { "ww.i.tau_avg",             &(cntrl_ww.i.tau_avg),             "%f" },
    { "ww.i.hzg_tvl_mw",          &(cntrl_ww.i.hzg_tvl_mw),          "%f" },
    { "ww.i.hzg_trl_mw",          &(cntrl_ww.i.hzg_trl_mw),          "%f" },
    { "ww.i.hk_tvl_sw",           &(cntrl_ww.i.hk_tvl_sw),           "%f" },
    { "ww.i.sp1_to_mw",           &(cntrl_ww.i.sp1_to_mw),           "%f" },
    { "ww.i.sp2_tu_mw",           &(cntrl_ww.i.sp2_tu_mw),           "%f" },
    { "ww.i.zirkzustand",         &(cntrl_ww.i.zirkzustand),         "%x" },

    { "ww.o.hzg_tvl_sw",          &(cntrl_ww.o.hzg_tvl_sw),          "%f" },
    { "ww.o.hzg_mv_y",            &(cntrl_ww.o.hzg_mv_y),            "%f" },
    { "ww.o.hzg_pu_y",            &(cntrl_ww.o.hzg_pu_y),            "%f" },
    { "ww.reg_pu.x[0]",           &(cntrl_ww.reg_pu.x[0]),           "%f" },
    { "ww.reg_pu.x[1]",           &(cntrl_ww.reg_pu.x[1]),           "%f" },
    { "ww.reg_pu.x[2]",           &(cntrl_ww.reg_pu.x[2]),           "%f" },
    { "ww.reg_pu.x[3]",           &(cntrl_ww.reg_pu.x[3]),           "%f" },
    { "ww.o..hzg_pu_sb",          &(cntrl_ww.o.hzg_pu_sb),           "%x" },
    { "ww.o.hzg_vv_sb",           &(cntrl_ww.o.hzg_vv_sb),           "%x" }
};

static const parse_set_t telnet_sol_Vars[] =
{
    { "sol.p.sp_t_max",        &(cntrl_sol.p.sp_t_max),        "%f" },
    { "sol.p.dt_ein_sw",       &(cntrl_sol.p.dt_ein_sw),       "%f" },
    { "sol.p.dt_aus_sw",       &(cntrl_sol.p.dt_aus_sw),       "%f" },
    { "sol.p.k_wlf",           &(cntrl_sol.p.k_wlf),           "%f" },

    { "sol.i.koll_t_mw[KO1]",  &(cntrl_sol.i.koll_t_mw[KO1]),  "%f" },
    { "sol.i.t_sp[SP1].to_mw", &(cntrl_sol.i.t_sp[SP1].to_mw), "%f" },
    { "sol.i.t_sp[SP1].tu_mw", &(cntrl_sol.i.t_sp[SP1].tu_mw), "%f" },
    { "sol.i.t_sp[SP2].to_mw", &(cntrl_sol.i.t_sp[SP2].to_mw), "%f" },
    { "sol.i.t_sp[SP2].tu_mw", &(cntrl_sol.i.t_sp[SP2].tu_mw), "%f" },

    { "sol.o.av_sb[SP1]",      &(cntrl_sol.o.av_sb[SP1]),      "%x" },
    { "sol.o.av_sb[SP2]",      &(cntrl_sol.o.av_sb[SP2]),      "%x" },
    { "sol.o.pu_sb[SP1]",      &(cntrl_sol.o.pu_sb[SP1]),      "%x" },

    { "sol.sol_wz",            &(cntrl_sol.sol_wz),            "%f" }
};

static const parse_set_t telnet_kes_Vars[] =
{
    { "kes.p.sp_dt_sw",     &(cntrl_kes.p.sp_dt_sw),     "%f" },
    { "kes.p.ww_tww_sw",    &(cntrl_kes.p.ww_tww_sw),    "%f" },

    { "kes.i.sp1_to_mw",    &(cntrl_kes.i.sp1_to_mw),    "%f" },
    { "kes.i.sp2_to_mw",    &(cntrl_kes.i.sp2_to_mw),    "%f" },
    { "kes.i.tvl_mw",       &(cntrl_kes.i.tvl_mw),       "%f" },
    { "kes.i.hk_tvl_sw",    &(cntrl_kes.i.hk_tvl_sw),    "%f" },
    { "kes.i.fb_tvl_sw",    &(cntrl_kes.i.fb_tvl_sw),    "%f" },
    { "kes.i.fb_prim_mv_y", &(cntrl_kes.i.fb_prim_mv_y), "%f" },
    { "kes.i.duschzeit",    &(cntrl_kes.i.duschzeit),    "%x" },
    { "kes.i.br_bm",        &(cntrl_kes.i.br_bm),        "%x" },

    { "kes.o.sp1_to_sw",    &(cntrl_kes.o.sp1_to_sw),    "%f" },
    { "kes.o.sp2_to_sw",    &(cntrl_kes.o.sp2_to_sw),    "%f" },
    { "kes.o.tvl_sw_sp1",   &(cntrl_kes.o.tvl_sw_sp1),   "%f" },
    { "kes.o.tvl_sw_sp2",   &(cntrl_kes.o.tvl_sw_sp2),   "%f" },
    { "kes.o.tvl_sw",       &(cntrl_kes.o.tvl_sw),       "%f" },
    { "kes.o.pu_sp1_sb",    &(cntrl_kes.o.pu_sp1_sb),    "%x" },
    { "kes.o.pu_sp2_sb",    &(cntrl_kes.o.pu_sp2_sb),    "%x" }
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



