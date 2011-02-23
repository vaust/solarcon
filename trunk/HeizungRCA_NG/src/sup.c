#define _SUP_C_

#include "gen_types.h"
#include "param.h"
#include "sup.h"

float sup_Limit( float value, const float lower_limit, const float upper_limit )
{
    float result;

    if( value <= lower_limit ) {
        result = lower_limit;
    }
    else if( value >= upper_limit ) {
        result = upper_limit;
    }
    else {
        result = value;
    }
    return( result );
}

void sup_DigRegInit( sup_digreg_coeff_t *q_p, 
                     sup_digreg_out_t   *y_p,
                     float               TA,
                     float               kp,
                     float               ki,
                     float               ap,
                     float               lower_limit,
                     float               upper_limit  )
{
    int n;
    
    q_p->TA = TA;
    q_p->kp = kp;
    q_p->ki = ki;
    q_p->ap = ap;
    q_p->lower_limit = lower_limit;
    q_p->upper_limit = upper_limit;
    for( n=0; n<SUP_REG_STATEVARS; n ++ ) y_p->x[n] = 0.0;
}


/**
 * \brief Digitaler PI-Regler mit Anti Windup.
 * Array x[] enthaelt die Zustandsgroessen.
 */

float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                           sup_digreg_out_t   *y_p )
{
    /* x[0] : x Eingangsgroesse                 */
    /* x[2] : y Ausgangsgroesse ohne Begrenzung */
    /* x[3] : Anti Windup Rueckfuehrung         */
    
    y_p->x[0] =  soll-ist;
    y_p->x[1] += q_p->ki * q_p->TA * y_p->x[0] - y_p->x[3]; 
    y_p->x[2] =  q_p->kp * y_p->x[0] + y_p->x[1] + q_p->ap;

    y_p->y = sup_Limit( y_p->x[2], q_p->lower_limit, q_p->upper_limit );
    y_p->x[3] = y_p->x[2] - y_p->y;
    
    return( y_p->y );
}

