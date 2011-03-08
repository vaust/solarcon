#ifndef _WW_H_
#define _WW_H_

#include "gen_types.h"
#include "reg.h"

/* <Defines> */
#define WW_VV_SP1       0x00
#define WW_VV_SP2       0x01
/* <Defines> */

/* <Typen> */
/** @brief Parameter der Komponente ww */
typedef struct ww_param_s {
    float kes_sp_dt_sw;
    float tww_sw;                   /**< Warmwasser Temperatur Sollwert                           */
    float frostschutz;              /**< Aussentemperatur ab der die Zirkulation dauerhaft laeuft */
    float at_start;
    float mv_korr;
    float hzg_pu_y_min;             /**< minimaler Prozentsatz ab der die Pumpe laeuft            */
    u16_t schwachlastzeit_max;
} ww_param_t;

/** @brief Eingangsgroessen der Komponente ww */
typedef struct ww_in_s {
    float tww_mw;
    float tau_mw;
    float tau_avg;
    u32_t wz_mw;                    /**< Zaehlerstand des Wasserzaehlers (noch nicht in Verwendung */
    float hzg_tvl_mw;
    float hzg_trl_mw;
    float hk_tvl_sw;
    float sp1_to_mw;
    float sp2_tu_mw;
    ein_aus_t  zirkzustand;
    nutzzeit_t duschzeit;
} ww_in_t;

/** @brief Ausgangsgroessen der Komponente ww */
typedef struct ww_out_s {
    float         hzg_tvl_sw;
    float         hzg_mv_y;
    float         hzg_pu_y;
    do_bitbyte_t  zirk_pu_sb;
    do_bitbyte_t  hzg_pu_sb;
    do_bitbyte_t  hzg_vv_sb;
} ww_out_t;

/** @brief Definition der Komponentenklasse ww */
typedef struct ww_class_s {
    reg_class_t reg_pu;
    reg_class_t reg_mv;
    ww_param_t  p;
    ww_in_t     i;
    ww_out_t    o;
} ww_class_t;

/* <Typen/> */

/* <Prototypen> */
void ww_Init( ww_class_t *self );
void ww_Run( ww_class_t *self );
void ww_WriteInp(       ww_class_t *self,
                  const float       tww_mw,
                  const float       tau_mw,
                  const float       tau_avg,
                  const u32_t       wz_mw,
                  const float       hzg_tvl_mw,
                  const float       hzg_trl_mw,
                  const float       hk_tvl_sw,
                  const float       sp1_to_mw,
                  const float       sp2_tu_mw,
                  const ein_aus_t   zirkzustand,
                  const nutzzeit_t  duschzeit    );
/* <Prototypen/> */

#endif /* _WW_H_ */

