#ifndef
#define _SUP_C_
#endif

#include "sup.h"
#include "gen_types.h"

float sup_Limit( float *value, const float lower_limit, const float upper_limit )
{
    if( *value <= lower_limit ) {
        *value = lower_limit;
    }
    else if( *value >= upper_limit ) {
        *value = upper_limit;
    }
    return( *value );
}

float sup_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, float *y )
{
    float xd;                  /* xd(t)   */
    static float xd_1 = 0.0;   /* xd(t-1) */
    static float y_1  = 0.0;   /* y(t-1)  */
    
    xd   = soll-ist;
    *y   = y_1 * q_p->q0*xd + q_p->q1*xd_1;
    y_1  = *y;
    xd_1 = xd;    
    limit(  y,   q_p->lower_limit, q_p->upper_limit );
    limit( &y_1, q_p->lower_limit, q_p->upper_limit );
    return( *y );
}

void ProzentToAnalogOut( float scale ,ao_0_10V_t *out_p )
{
    *out_p = (ao_0_10V_t) ((scale*VFULLSCALE)/100);
}

