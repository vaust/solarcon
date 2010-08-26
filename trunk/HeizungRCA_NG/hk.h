/* <Typen> */
typedef struct {
    float reg_kp;
    float reg_tn;
    float TA;
    float tvl_absenk;
    float tvl_steigung;
    float tvl_niveau;
    float tvl_min;
    float tvl_max;
    float at_start;
    float q0;
    float q1;
    float frostschutz;
} hk_param_t;

typedef struct {
    float tau_mw;
    float tau_avg;
    float tr_sw;
    float tvl_mw;
    xx_t  zustand;
    xx_t  partytime_flg; 
} hk_in_t;

typedef struct {
    float tvl_sw;
    float mv_y;
    float mv_y_alt;
    unsigned char pu_sb;  
} hk_out_t;
/* <Typen/> */

/* <Prototypen> */
void hk_Init( hk_param_t *par_p, hk_out_t *out_p );
void hk_Run( const hk_param_t *par_p, const hk_int_t *in_p, hk_out_t *out_p );
/* <Prototypen/> */