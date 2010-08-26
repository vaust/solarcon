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
} fb_param_t;

typedef struct {
    float tau_mw;
    float tau_avg;
    float tr_sw;
    float sek_tvl_mw;
    xx_t  zustand;
    xx_t  partytime_flg; 
} fb_in_t;

typedef struct {
    float tvl_sw;
    float prim_mv_y;
    float prim_mv_y_alt;
    unsigned char prim_pu_sb;
    unsigned char sek_pu_sb;
    
} fb_out_t;
/* <Typen/> */

/* <Prototypen> */
void limit( float *value, const float lower_limit, const float upper_limit );
void fb_Init( fb_param_t *par_p, fb_out_t *out_p );
void fb_Run( const fb_param_t *par_p, const fb_int_t *in_p, fb_out_t *out_p )
/* <Prototypen/> */
