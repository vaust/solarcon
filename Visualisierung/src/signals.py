'''
Created on 23.01.2012

@author: stegmv
'''
# -*- coding: utf-8 -*-

TEMP_NAMES = { "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel", "Tau_36h_mittel" }        

PU_NAMES = { "WW_HZG_PU_SB", "HK_PU_SB", "WW_ZIRK_PU_SB", "HK_PU_SB", "FB_SEK_PU_SB", "FB_PRIM_PU_SB",
             "KES_PU_SP1_SB", "KES_PU_SP2_SB", "SOL_PU_SB" }

AO_NAMES = { "WW_HZG_MV_Y", "FB_PRIM_MV_Y", "HK_MV_Y", "WW_HZG_VV_Y", "WW_HZG_PU_Y" }

CNT_NAMES = { "WW_WZ_MW" }

AV_NAMES = { "SOL_SP1_AV_SB", "SOL_SP2_AV_SB" }

DI_NAMES = { "ALL_PARTY", "WW_PARTY" }

PARAMETERS = {
  "ALL_Tau_mittel_Zeit", "ALL_Partydauer", "ALL_Frostschutz", "ALL_AT_Start", "SOL_dT_ein_SW"
, "SOL_dT_aus_SW", "SOL_KOLL_T_max", "SOL_SP_T_max", "SOL_SP1_T_min", "KES_SP_dT_SW"
, "HK_Tvl_Steigung", "HK_Tvl_Niveau", "HK_Tvl_Absenk", "HK_Tvl_Min", "HK_Tvl_Max", "HK_Frostschutz"
, "HK_REG_Kp", "HK_REG_Ki", "HK_REG_AP", "HK_Tr_SW"
, "FB_Tvl_Steigung", "FB_Tvl_Niveau", "FB_Tr_SW", "FB_Tvl_Absenk", "FB_Tvl_Min", "FB_Tvl_Max", "FB_REG_Kp"
, "FB_REG_Ki", "FB_REG_AP"
, "WW_Tww_SW", "WW_Tww_Max", "WZ_Faktor", "WZ_Max", "WW_PU_REG_Kp", "WW_PU_REG_Ki", "WW_PU_REG_AP"
, "WW_MV_KORR", "WW_Tww_Tvl_Faktor", "WW_Tz_SW"
, "SYS_Zykluszeit"
}
