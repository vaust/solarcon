#define _REG_C_

#include "gen_types.h"
#include "param.h"
#include "reg.h"

float reg_Limit( float value, const float lower_limit, const float upper_limit )
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

/*
void sup_DigRegInit( sup_digreg_coeff_t *q_p, 
                     sup_digreg_out_t   *y_p,
                     float               TA,
                     float               kp,
                     float               ki,
                     float               ap,
                     float               lower_limit,
                     float               upper_limit  )
*/
void reg_PI_Init(       reg_class_t *self,
                  const float        TA,
                  const float        kp,
                  const float        ki,
                  const float        ap,
                  const float        lower_limit,
                  const float        upper_limit,
                        float const *y,
                        float const *soll,
                        float const *ist            )
{
    int n;
    
    self->p.TA = TA;
    self->p.kp = kp;
    self->p.ki = ki;
    self->p.ap = ap;
    self->p.lower_limit = lower_limit;
    self->p.upper_limit = upper_limit;
    self->y    = y;
    self->soll = soll;
    self->ist  = ist;
    for( n=0; n<SUP_REG_STATEVARS; n ++ ) self->x[n] = 0.0;
}


/**
 * \brief Digitaler PI-Regler mit Anti Windup.
 * Array x[] enthaelt die Zustandsgroessen.
 */

float reg_PI_Run( reg_class_t *self )
{
    /* x[0] : x Eingangsgroesse                 */
    /* x[2] : y Ausgangsgroesse ohne Begrenzung */
    /* x[3] : Anti Windup Rueckfuehrung         */
    
    self->x[0] =  *(self->soll) - *(self->ist);
    self->x[1] += self->p.ki * self->p.TA * self->x[0] - self->x[3];
    self->x[2] =  self->p.kp * self->x[0] + self->x[1] + self->p.ap;

    *(self->y) = sup_Limit( self->x[2], self->p.lower_limit, self->p.upper_limit );
    self->x[3] = self->x[2] - *(self->y);
    
    return( *(self->y) );
}

