#ifndef _TELNET_VARS_H_
#define _TELNET_VARS_H_

const parse_set_t telnet_fb_Vars[] =
{
    { "fb_par.reg_kp",         &(cntrl_fb_par.reg_kp),         "%f" },
    { "fb_par.reg_ki",         &(cntrl_fb_par.reg_ki),         "%f" },
    { "fb_par.reg_tn",         &(cntrl_fb_par.reg_tn),         "%f" },
    { "fb_par.TA",             &(cntrl_fb_par.TA),             "%f" },
    { "fb_par.tvl_absenk",     &(cntrl_fb_par.tvl_absenk),     "%f" },
    { "fb_par.tvl_steigung",   &(cntrl_fb_par.tvl_steigung),   "%f" },
    { "fb_par.tvl_niveau",     &(cntrl_fb_par.tvl_niveau),     "%f" },
    { "fb_par.tvl_min",        &(cntrl_fb_par.tvl_min),        "%f" },
    { "fb_par.tvl_max",        &(cntrl_fb_par.tvl_max),        "%f" },
    { "fb_par.at_start",       &(cntrl_fb_par.at_start),       "%f" },
    { "fb_par.frostschutz",    &(cntrl_fb_par.frostschutz),    "%f" },
    { "fb_par.tr_sw",          &(cntrl_fb_par.tr_sw),          "%f" },

    { "fb_in.tau_mw",          &(cntrl_fb_in.tau_mw),          "%f" },
    { "fb_in.sek_tvl_mw",      &(cntrl_fb_in.sek_tvl_mw),      "%f" },
    { "fb_in.zustand",         &(cntrl_fb_in.zustand),         "%x" },
    { "fb_in.partytime_flg",   &(cntrl_fb_in.partytime_flg),   "%x" },

    { "fb_out.tvl_sw",         &(cntrl_fb_out.tvl_sw),         "%f" },
    { "fb_out.prim_mv_y.y",    &(cntrl_fb_out.prim_mv_y.y),    "%f" },
    { "fb_out.prim_mv_y.x[0]", &(cntrl_fb_out.prim_mv_y.x[0]), "%f" },
    { "fb_out.prim_mv_y.x[1]", &(cntrl_fb_out.prim_mv_y.x[1]), "%f" },
    { "fb_out.prim_mv_y.x[2]", &(cntrl_fb_out.prim_mv_y.x[2]), "%f" },
    { "fb_out.prim_mv_y.x[3]", &(cntrl_fb_out.prim_mv_y.x[3]), "%f" },
    { "fb_out.prim_pu_sb",     &(cntrl_fb_out.prim_pu_sb),     "%x" },
    { "fb_out.sek_pu_sb",      &(cntrl_fb_out.sek_pu_sb),      "%x" },

    { "fb_q.TA",               &(cntrl_fb_q.TA),               "%f" },
    { "fb_q.kp",               &(cntrl_fb_q.kp),               "%f" },
    { "fb_q.ki",               &(cntrl_fb_q.ki),               "%f" },
    { "fb_q.lower_limit",      &(cntrl_fb_q.lower_limit),      "%f" },
    { "fb_q.upper_limit",      &(cntrl_fb_q.upper_limit),      "%f" }
};

const parse_set_t telnet_hk_Vars[] =
{
    { "hk_par.reg_kp",         &(cntrl_hk_par.reg_kp),         "%f" },
    { "hk_par.reg_ki",         &(cntrl_hk_par.reg_ki),         "%f" },
    { "hk_par.reg_tn",         &(cntrl_hk_par.reg_tn),         "%f" },
    { "hk_par.TA",             &(cntrl_hk_par.TA),             "%f" },
    { "hk_par.tvl_absenk",     &(cntrl_hk_par.tvl_absenk),     "%f" },
    { "hk_par.tvl_steigung",   &(cntrl_hk_par.tvl_steigung),   "%f" },
    { "hk_par.tvl_niveau",     &(cntrl_hk_par.tvl_niveau),     "%f" },
    { "hk_par.tvl_min",        &(cntrl_hk_par.tvl_min),        "%f" },
    { "hk_par.tvl_max",        &(cntrl_hk_par.tvl_max),        "%f" },
    { "hk_par.at_start",       &(cntrl_hk_par.at_start),       "%f" },
    { "hk_par.frostschutz",    &(cntrl_hk_par.frostschutz),    "%f" },
    { "hk_par.tr_sw",          &(cntrl_hk_par.tr_sw),          "%f" },

    { "hk_in.tau_mw",          &(cntrl_hk_in.tau_mw),          "%f" },
    { "hk_in.tau_avg",         &(cntrl_hk_in.tau_avg),         "%f" },
    { "hk_in.tvl_mw",          &(cntrl_hk_in.tvl_mw),          "%f" },
    { "hk_in.zustand",         &(cntrl_hk_in.zustand),         "%x" },
    { "hk_in.partytime_flg",   &(cntrl_hk_in.partytime_flg),   "%x" },

    { "hk_out.tvl_sw",         &(cntrl_hk_out.tvl_sw),         "%f" },
    { "hk_out.mv_y.y",         &(cntrl_hk_out.mv_y.y),         "%f" },
    { "hk_out.mv_y.x[0]",      &(cntrl_hk_out.mv_y.x[0]),      "%f" },
    { "hk_out.mv_y.x[1]",      &(cntrl_hk_out.mv_y.x[1]),      "%f" },
    { "hk_out.mv_y.x[2]",      &(cntrl_hk_out.mv_y.x[2]),      "%f" },
    { "hk_out.mv_y.x[3]",      &(cntrl_hk_out.mv_y.x[3]),      "%f" },
    { "hk_out.pu_sb",          &(cntrl_hk_out.pu_sb),          "%x" },

    { "hk_q.TA",               &(cntrl_hk_q.TA),               "%f" },
    { "hk_q.kp",               &(cntrl_hk_q.kp),               "%f" },
    { "hk_q.ki",               &(cntrl_hk_q.ki),               "%f" },
    { "hk_q.lower_limit",      &(cntrl_hk_q.lower_limit),      "%f" },
    { "hk_q.upper_limit",      &(cntrl_hk_q.upper_limit),      "%f" }
};

const parse_set_t telnet_ww_Vars[] =
{
    { "ww_par.pu_reg_kp",           &(cntrl_ww_par.pu_reg_kp),           "%f" },
    { "ww_par.pu_reg_ki",           &(cntrl_ww_par.pu_reg_ki),           "%f" },
    { "ww_par.pu_reg_tn",           &(cntrl_ww_par.pu_reg_tn),           "%f" },
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
    { "ww_q.lower_limit",      &(cntrl_ww_q.lower_limit),      "%f" },
    { "ww_q.upper_limit",      &(cntrl_ww_q.upper_limit),      "%f" }
};

const parse_set_t telnet_sol_Vars[] =
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

const parse_set_t telnet_kes_Vars[] =
{
    { "kes_par.TA",           &(cntrl_kes_par.TA),           "%f" },
    { "kes_par.tvl_absenk",   &(cntrl_kes_par.tvl_absenk),   "%f" },
    { "kes_par.tvl_steigung", &(cntrl_kes_par.tvl_steigung), "%f" },
    { "kes_par.tvl_niveau",   &(cntrl_kes_par.tvl_niveau),   "%f" },
    { "kes_par.tvl_min",      &(cntrl_kes_par.tvl_min),      "%f" },
    { "kes_par.tvl_max",      &(cntrl_kes_par.tvl_max),      "%f" },
    { "kes_par.at_start",     &(cntrl_kes_par.at_start),     "%f" },
    { "kes_par.frostschutz",  &(cntrl_kes_par.frostschutz),  "%f" },
    { "kes_par.sp_dt_sw",     &(cntrl_kes_par.sp_dt_sw),     "%f" },
    { "kes_par.ww_tww_sw",    &(cntrl_kes_par.ww_tww_sw),    "%f" },

    { "kes_in.sp1_to_mw",     &(cntrl_kes_in.sp1_to_mw),     "%f" },
    { "kes_in.sp1_tu_mw" ,    &(cntrl_kes_in.sp1_tu_mw),     "%f" },
    { "kes_in.sp2_to_mw",     &(cntrl_kes_in.sp2_to_mw),     "%f" },
    { "kes_in.sp2_tu_mw" ,    &(cntrl_kes_in.sp2_tu_mw),     "%f" },
    { "kes_in.tvl_mw",        &(cntrl_kes_in.tvl_mw),        "%f" },
    { "kes_in.hk_tvl_sw",     &(cntrl_kes_in.hk_tvl_sw),     "%f" },
    { "kes_in.fb_tvl_sw",     &(cntrl_kes_in.fb_tvl_sw),     "%f" },
    { "kes_in.duschzeit",     &(cntrl_kes_in.duschzeit),     "%x" },
    { "kes_in.partytime_flg", &(cntrl_kes_in.partytime_flg), "%x" },
    { "kes_in.br_bm",         &(cntrl_kes_in.br_bm),         "%x" },

    { "kes_out.sp1_to_sw",    &(cntrl_kes_out.sp1_to_sw),    "%f" },
    { "kes_out.sp2_to_sw",    &(cntrl_kes_out.sp2_to_sw),    "%f" },
    { "kes_out.tvl_sw_sp1",   &(cntrl_kes_out.tvl_sw_sp1),   "%f" },
    { "kes_out.tvl_sw_sp2",   &(cntrl_kes_out.tvl_sw_sp2),   "%f" },
    { "kes_out.tvl_sw",       &(cntrl_kes_out.tvl_sw),       "%f" },
    { "kes_out.pu_sp1_sb",    &(cntrl_kes_out.pu_sp1_sb),    "%x" },
    { "kes_out.pu_sp2_sb",    &(cntrl_kes_out.pu_sp2_sb),    "%x" }
};

const char *telnet_help_text[] = {
    "\n Mögliche Befehle: \n\n",
    "\t GET T     (alle Temperaturmesswerte)\n",
    "\t GET SW    (Sollwerte)\n",
    "\t GET AO    (alle Analog-Ausgaenge)\n",
    "\t GET DI    (alle Digital-Eingaenge)\n",
    "\t GET DO    (alle Digital-Ausgaenge)\n",
    "\t GET FB    (Daten zu FB-Heizung)\n",
    "\t GET WW    (Daten zu Warmwasserbereitung)\n",
    "\t GET SOL   (Daten zu Solarbeheizung)\n",
    "\t GET HK    (Daten zu Heizkoerper-Heizkreis)\n",
    "\t GET PAR   (Eingelesene Parameter ausgeben)\n",
    "\t GET ZEIT  (Eingelesenes Zeitprogramm ausgeben)\n",
    "\t GET ABS   (Absenkungen ausgeben)\n\n",
    "\t INIT      (Initialisierungsdateien neu einlesen)\n\n",

    "\t AUTO <mdl>    (Modul SOL, FB, HK, WW, KES auf Automatik)\n",
    "\t AUTO ALL      (alle Module auf Automatik)\n",
    "\t HAND <mdl>    (Modul SOL, FB, HK, WW, KES auf Handbetrieb)\n",
    "\t MODUL         (Anzeige aller Module incl. Betriebszustand)\n",
    "\t PUT <mdl> var-nr=wert (Modul Variable manuell setzen.\n",
    "\t           Ausgangsgroessen sind nur im Handbetrieb aenderbar.\n",
    "\t           var-nr ergibt sich aus Ausgabe von GET Vxxx)\n\n",

    "\t GET VFB   (FB Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n",
    "\t GET VHK   (HK Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n",
    "\t GET VWW   (WW Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n",
    "\t GET VSOL  (SOL Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n",
    "\t GET VKES  (KES Modul: Parameter-, Eingangs- und Ausgangsvariablen)\n\n",
    "\t HELP      (Diesen Hilfetext ausgeben)\n",
    "\t VERSION   (Software Version ausgeben)\n",
    "\t END       (Datenabfrage beenden)\n\n"
};

#endif // _TELNET_VARS_H_
