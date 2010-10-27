#define _SUP_C_

#include "gen_types.h"
#include "param.h"
#include "sup.h"

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

void sup_DigRegInit( sup_digreg_coeff_t *q_p, 
                     sup_digreg_out_t   *y_p,
                     float               TA,
                     float               kp,
                     float               ki,
                     float               lower_limit,
                     float               upper_limit  )
{
    int n;
    
    q_p->TA = TA;
    q_p->kp = kp;
    q_p->ki = ki;
    q_p->lower_limit = lower_limit;
    q_p->upper_limit = upper_limit;
    for( n=0; n<SUP_REG_STATEVARS; n ++ ) y_p->x[n] = 0.0;
}


/*
 * Implementierung mit Anti Windup und Zustandgroessen 
 */

float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                            sup_digreg_out_t  *y_p )
{
    /* x[0] : x Eingangsgroesse */
    /* x[2] : y Ausgangsgroesse ohne Begrenzung */
    
    y_p->x[0] =  soll-ist;
    y_p->x[1] += q_p->ki * q_p->TA * y_p->x[0] - y_p->x[3]; 
    y_p->x[2] =  q_p->kp * y_p->x[0] + y_p->x[1];

    if ( y_p->x[2] > q_p->upper_limit )
        y_p->y = q_p->upper_limit;
    else if ( y_p->x[2] <= q_p->lower_limit )
        y_p->y = q_p->lower_limit;
    else
        y_p->y = y_p->x[2];
    
    y_p->x[3] = y_p->x[2] - y_p->y; /* x[3] : Anti Windup Rueckfuehrung */
    return( y_p->y );
}

