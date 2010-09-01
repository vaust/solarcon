#ifndef _INIT_H_
#define _INIT_H_

#include "vorgabe.h"

/* <Defines> */
#define PARSE_SET_N 36
/* <Defines/> */

/* <Typen> */

typedef struct {
    char *VarName;
    void *VarPointer;
    char *format;
} parse_set_t;

/* <Typen/> */

/* <Konstanten> */
#ifdef _INIT_C_
static const parse_set_t Vorgaben[PARSE_SET_N] = {
    { "ALL_Tau_mittel_Zeit", &all_tau_mittel_zeit, "%d" }, //  0
    { "ALL_Partydauer",      &all_partydauer,      "%d" }, //  1
    { "ALL_Frostschutz",     &all_frostschutz,     "%f" }, //  2
    { "ALL_AT_Start",        &all_at_start,        "%f" }, //  3
    { "SOL_dT_ein_SW",       &sol_dt_ein_sw,       "%f" }, //  4
    { "SOL_dT_aus_SW",       &sol_dt_aus_sw,       "%f" }, //  5
    { "SOL_KOLL_T_max",      &sol_koll_t_max,      "%f" }, //  6
    { "SOL_SP_T_max",        &sol_sp_t_max,        "%f" }, //  7
    { "SOL_SP1_T_min",       &sol_sp1_t_min,       "%f" }, //  8
    { "KES_SP_dT_SW",        &kes_sp_dt_sw,        "%f" }, //  9
    { "HK_Tvl_Steigung",     &hk_tvl_steigung,     "%f" }, // 10
    { "HK_Tvl_Niveau",       &hk_tvl_niveau,       "%f" }, // 11 
    { "HK_Tvl_Absenk",       &hk_tvl_absenk,       "%f" }, // 12
    { "HK_Tvl_Min",          &hk_tvl_min,          "%f" }, // 13
    { "HK_Tvl_Max",          &hk_tvl_max,          "%f" }, // 14
    { "HK_Frostschutz",      &hk_frostschutz,      "%f" }, // 15
    { "HK_REG_Kp",           &hk_reg_kp,           "%f" }, // 16
    { "HK_REG_Tn",           &hk_reg_tn,           "%f" }, // 17
    { "HK_Tr_SW",            &hk_tr_sw,            "%f" }, // 18
    { "FB_Tvl_Steigung",     &fb_tvl_steigung,     "%f" }, // 19
    { "FB_Tvl_Niveau",       &fb_tvl_niveau,       "%f" }, // 20
    { "FB_Tr_SW",            &fb_tr_sw,            "%f" }, // 21
    { "FB_Tvl_Absenk",       &fb_tvl_absenk,       "%f" }, // 22
    { "FB_Tvl_Min",          &fb_tvl_min,          "%f" }, // 23
    { "FB_Tvl_Max",          &fb_tvl_max,          "%f" }, // 24
    { "FB_REG_Kp",           &fb_reg_kp,           "%f" }, // 25
    { "FB_REG_Tn",           &fb_reg_tn,           "%f" }, // 26
    { "WW_Tww_SW",           &ww_tww_sw,           "%f" }, // 27
    { "WW_Tww_Max",          &ww_tww_max,          "%f" }, // 28
    { "WZ_Faktor",           &wz_faktor,           "%f" }, // 29
    { "WZ_Max",              &wz_max,              "%f" }, // 30  
    { "WW_PU_REG_Kp",        &ww_pu_reg_kp,        "%f" }, // 31
    { "WW_PU_REG_Tn",        &ww_pu_reg_tn,        "%f" }, // 32
    { "WW_MV_KORR",          &ww_mv_korr,          "%f" }, // 33
    { "WW_Tww_Tvl_Faktor",   &ww_tww_tvl_faktor,   "%f" }, // 34
    { "WW_Tz_SW",            &ww_tz_sw,            "%f" }  // 35
};                                                         
#endif /* _INIT_C_ */

/* <Konstanten/> */
#endif

