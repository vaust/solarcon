
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

void hk_Init( hk_param_t *par_p, hk_out_t *out_p  )
{
    par_p->q0 =  par_p->reg_kp + par_p->TA/par_p->reg_tn;
    par_p->q1 = -par_p->reg_kp;
    out_p->prim_mv_y_alt = 50.0;
}    

/* Regler fuer den Waermetauscher, der den Heizkoerperheizkreis beheizt */
void hk_Run( const hk_param_t *par_p, const hk_int_t *in_p, hk_out_t *out_p )
{
    float           xd;             /* Regelabweichung      */
    static float    xd_alt = 0.0;

    /* Vorlauftemperatursollwert im Floatformat berechnen   */
    out_p->tvl_sw = (in_p->tr_sw - in_p->tau_mw) * par_p->tvl_steigung + in_p->tr_sw + par_p->tvl_niveau;
    if( (in_p->zustand == zAbgesenkt) && (in_p->partytime_flg == RESET) ) {
        out_p->tvl_sw -= par_p->tvl_absenk;
    }
    limit( &(out_p->tvl_sw), par_p->tvl_min, par_p->tvl_max );

    /* Regelabweichung Soll - Ist */
    xd = out_p->tvl_sw - in_p->tvl_mw;
    /* Mischventil ueber PI-Regler ansteuern */
    out_p->mv_y = out_p->mv_y_alt + q0*xd + q1*xd_alt ;
    out_p->mv_y_alt = out_p->mv_y;
    xd_alt = xd;

    limit( &(out_p->prim_mv_y),     MIN_Y_PCT, MAX_Y_PCT );
    limit( &(out_p->prim_mv_y_alt), MIN_Y_PCT, MAX_Y_PCT );

    if( (in_p->tau_avg < par_p->at_start) &&        /* mittlere AT unter Betriebsschwelle */          
        (out_p->tvl_sw > 30.0           )    )      /* VL-Temp. ab der HK wirklich heizt */ 
        out_p->pu_sb = IO_EIN;                          /* Heizkreis Pumpe einschalten */
    else if( in_p->tau_avg > (par_p->at_start+1.0) )
        out_p->pu_sb = IO_AUS;                          /* Heizkreis Pumpe ausschalten */
    else if (in_p->tau_mw <  all_frostschutz )        /* AT unter Frostschutzmarke */
        out_p->pu_sb = IO_EIN;                          /* Heizkreis Pumpe einschalten */
}
