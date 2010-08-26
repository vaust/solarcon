
/* <Prototypen> */
void limit( float *value, const float lower_limit, const float upper_limit )
/* <Prototypen/> */

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

void limit( float *value, const float lower_limit, const float upper_limit )
{
    if( *value <= lower_limit ) {
        *value = lower_limit;
    } 
    else if( *value >= upper_limit ) {
        *value = upper_limit
    }
}

void fb_Init( fb_param_t *par_p, fb_out_t *out_p  )
{
    par_p->q0 =  par_p->reg_kp + par_p->TA/par_p->reg_tn;
    par_p->q1 = -par_p->reg_kp;
    out_p->prim_mv_y_alt = 50.0;
}    

void fb_Run( const fb_param_t *par_p, const fb_int_t *in_p, fb_out_t *out_p )
{
    float        xd;                  /* Regelabweichung               */
    static float xd_alt = 0.0;        /* vorhergehende Regelabweichung */

    /* Vorlauftemperatursollwert im Floatformat berechnen  */
    out_p->tvl_sw =  (par_p->tr_sw - par_p->tau_mw) * par_p->tvl_steigung 
                    + par_p->tr_sw + par_p->tvl_niveau;
    if( (in_p->zustand == zAbgesenkt) && (in_p->partytime_flg == RESET) ) {
        out_p->tvl_sw -= par_p->tvl_absenk;
    }
    limit( &(out->tvl_sw), par_p->tvl_min, par_p->tvl_max );
 
    /* Mischventil PI-Regleralgorithmus */
    xd               = out_p->tvl_sw - in_p->sek_tvl_mw;
    out_p->prim_mv_y = prim_mv_y_alt + par_p->q0*xd + par_p->q1*xd_alt ;
    prim_mv_y_alt    = out_p->prim_mv_y;
    xd_alt           = xd;

    /* Mischventil mit 0-10V ansteuern */
    limit( &(out_p->prim_mv_y),     MIN_Y_PCT, MAX_Y_PCT );
    limit( &(out_p->prim_mv_y_alt), MIN_Y_PCT, MAX_Y_PCT );
       
    if(   (in_p->tau_avg <  par_p->at_start) && /* Die mittlere Aussentemperatur liegt unter der Betriebsschwelle */
          (out_p->tvl_sw >  20.0           )    /* Der berechnete Vorlauftemperatursollwert liegt unter 20°C      */
        ) {
        out_p->prim_pu_sb = IO_EIN;
        out_p->sek_pu_sb  = IO_EIN;
    }
    else if( in_p->tau_avg > (par_p->at_start+1.0) ) {
        out_p->prim_pu_sb = IO_AUS;
        out_p->sek_pu_sb  = IO_AUS;
    }
    else if( in_p->tau_mw < par_p->frostschutz ) {
        out_p->prim_pu_sb = IO_EIN;
        out_p->sek_pu_sb  = IO_EIN;
    }
}
