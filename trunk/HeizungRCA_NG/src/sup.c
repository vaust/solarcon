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
    int n;
    
    y_p->xd_1 = 0.0;
    y_p->y    = 50.0; /* % */
    y_p->y_1  = 50.0; /* % */
    for( n=0; n<8; n ++ ) y_p->x[n] = 0.0;
}

float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                           sup_digreg_out_t   *y_p )
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

/*
 * Implementierung mit Anti Windup und Zustandgroessen 
 */

float sup_DigRegler2( const sup_digreg_coeff_t *q_p, 
                      const float               soll, 
                      const float               ist, 
                            sup_digreg_out_t   *y_p )
{
    /* x[0] : x Eingangsgroesse */
    /* x[7] : y Ausgangsgroesse */
    
    y_p->x[0] = soll-ist;
    y_p->x[1] = q_p->kp * y_p->x[0];
    y_p->x[2] = q_p->ki * y_p->x[0];
    y_p->x[3] = y_p->x[2] + y_p->x[4] - y_p->x[6]; /* x[4] = z^(-1)*x[3]         */
    y_p->x[4] = y_p->x[3]; /* neuer x[3] ist jetzt x[4] fuer naechsten Durchlauf */
    y_p->x[5] = y_p->x[1] + y_p->x[3];

    if ( y_p->x[5] >= q_p->upper_limit )
        y_p->x[7] = q_p->upper_limit;
    else if ( y_p->x[5] < q_p->lower_limit )
        y_p->x[7] = q_p->lower_limit;

    y_p->x[6] = y_p->x[5] - y_p->x[7];
    y_p->y = y_p->x[7];
    return( y_p->y );
}

