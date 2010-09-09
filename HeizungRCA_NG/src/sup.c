#define _SUP_C_

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

void sup_DigRegInit( sup_digreg_coeff_t *q_p, sup_digreg_out_t *y_p )
{
    y_p->xd_1 = 0.0;
    y_p->y    = 50.0; /* % */
    y_p->y_1  = 50.0; /* % */
}

float sup_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, sup_digreg_out_t *y_p )
{
    float xd; /* xd(t)   */

    xd   = soll-ist;
    y_p->y    = y_p->y_1 + q_p->q0*xd + q_p->q1*y_p->xd_1;
    y_p->y_1  = y_p->y;
    y_p->xd_1 = xd;
    sup_Limit( &(y_p->y  ), q_p->lower_limit, q_p->upper_limit );
    sup_Limit( &(y_p->y_1), q_p->lower_limit, q_p->upper_limit );
    return( y_p->y );
}

void sup_YToAnalog( float scale ,ao_0_10V_t *out_p )
{
    *out_p = (ao_0_10V_t) ((scale*VFULLSCALE)/100);
}

