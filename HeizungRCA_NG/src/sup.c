#define _SUP_C_

#include "sup.h"
#include "gen_types.h"

float sup_Limit( float *value, const float lower_limit, const float upper_limit )
{
    if( *value <= lower_limit ) {
        *value = lower_limit;
    }
    else if( *value > upper_limit ) {
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

float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                           sup_digreg_out_t   *y_p )
{
    float xd;       /* xd(t) */

    xd     = soll-ist;
    y_p->y = y_p->y_1 + q_p->q0*xd + q_p->q1*y_p->xd_1;

    /* Anti Windup Algorithmus */
    if( y_p->y > q_p->upper_limit )  
        y_p->y -= q_p->antiwup * (y_p->y - q_p->upper_limit);
    else if( y_p->y < q_p->lower_limit ) 
        y_p->y -= q_p->antiwup * (y_p->y - q_p->lower_limit);

    /* Begrenzung nur zur Sicherheit: Werte sollten dank Anti Windup *
     * immer unter Grenze liegen.                                    */
    sup_Limit( &(y_p->y  ), q_p->lower_limit, q_p->upper_limit );   
    sup_Limit( &(y_p->y_1), q_p->lower_limit, q_p->upper_limit );

    y_p->y_1  = y_p->y;
    y_p->xd_1 = xd;

    return( y_p->y );
}

