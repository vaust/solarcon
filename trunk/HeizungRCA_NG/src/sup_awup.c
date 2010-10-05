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

// float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     // const float               soll, 
                     // const float               ist, 
                           // sup_digreg_out_t   *y_p )
// {
    // float xd;       /* xd(t) */
    
    
    // xd     = soll-ist;
    // y_p->y = y_p->y_1 + q_p->q0*xd + q_p->q1*y_p->xd_1;

    // /* Anti Windup Algorithmus */
    // if( y_p->y > q_p->upper_limit )  
        // y_p->y_1 += q_p->antiwup * (y_p->y - q_p->upper_limit);
    // else if( y_p->y < q_p->lower_limit ) 
        // y_p->y_1 += q_p->antiwup * (y_p->y - q_p->lower_limit);

    // y_p->y_1  = y_p->y;
    // y_p->xd_1 = xd;
    // sup_Limit( &(y_p->y  ), q_p->lower_limit, q_p->upper_limit );   

    // return( y_p->y );
// }

float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                           sup_digreg_out_t   *y_p )
{
    float x[8]; /* Zustandsgroessen des Algos */
    /* x[0] : x Eingangsgrosse  */
    /* x[7] : y Ausgangsgroesse */
    
    x[1] = KP * x[0];
    x[2] = KI * x[0];
    x[3] = x[4] + x[2] - x[6]; /* x[4] = z^(-1)*x[3] */
    x[4] = x[3];
    x[5] = x[1] + x[3];
    x[7] = (x[5] > q_p->upper_limit ? q_p->upper_limit : x[5]) < q_p->lower_limit ? q_p->lower_limit : x[5];
    x[6] = x[5] - x[7];
}

    
    
    
    
    
    
    
    
