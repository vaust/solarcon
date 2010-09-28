#ifndef _WW_H_
#define _WW_H_

#include "sup.h"
#include "gen_types.h"

/* <Defines> */
#define WW_VV_SP1       0x00
#define WW_VV_SP2       0x01
/* <Defines> */

/* <Typen> */
typedef struct {
    float pu_reg_kp;        
    float pu_reg_tn;
    // float mv_reg_kp;   Momentan nicht in Verwendung
    // float mv_reg_tn;   Momentan nicht in Verwendung
    float TA;
    float kes_sp_dt_sw;
    float tww_sw;                   /**< Warmwasser Temperatur Sollwert */
    float frostschutz;              /**< Aussentemperatur ab der die Zirkulation dauerhaft laeuft */
    float at_start;
    float mv_korr;
    float hzg_pu_y_min;             /**< minimaler Prozentsatz ab der die Pumpe laeuft            */
    u16_t schwachlastzeit_max;
} ww_param_t;

typedef struct {
    float tww_mw;
    float tau_mw;
    float tau_avg;
    u32_t wz_mw;                    /**< Zaehlerstand des Wasserzaehlers (noch nicht in Verwendung */
    float hzg_tvl_mw;
    float hzg_trl_mw;
    float hk_tvl_sw;
    float sp1_to_mw;
    float sp2_tu_mw;
    ein_aus_t zirkzustand;
} ww_in_t;

typedef struct {
    float            hzg_tvl_sw;
    sup_digreg_out_t hzg_mv_y;
    sup_digreg_out_t hzg_pu_y;
    do_bitbyte_t     zirk_pu_sb;  
    do_bitbyte_t     hzg_pu_sb;
    do_bitbyte_t     hzg_vv_sb;    
} ww_out_t;

/* <Typen/> */

/* <Prototypen> */
#ifdef _WW_C_
static void ww_MV_Steuerung( const ww_param_t *par_p, 
                             const ww_in_t    *in_p, 
                                   ww_out_t   *out_p );
                            
static void ww_VV_Steuerung( const ww_param_t *par_p, 
                             const ww_in_t    *in_p, 
                                   ww_out_t   *out_p );
              
static void ww_Schwachlast_Steuerung( const ww_param_t *par_p, 
                                            ww_out_t   *out_p );
#endif // _WW_C_
              
void ww_Init( ww_param_t         *par_p, 
              sup_digreg_coeff_t *q_hzg_pu_p,
              ww_out_t           *out_p );
                    
void ww_Run( const ww_param_t         *par_p, 
             const sup_digreg_coeff_t *q_hzg_pu_p, 
             const ww_in_t            *in_p, 
                   ww_out_t           *out_p );
/* <Prototypen/> */

#endif /* _WW_H_ */

