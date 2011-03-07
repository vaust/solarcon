/**
 * @file reg.c
 * @brief Implementierung einer PI Regler Klasse
 * @author Volker Stegmann
 */

#define _REG_C_

#include "gen_types.h"
#include "param.h"
#include "reg.h"

/**
 * @brief Limitierungsfunktion
 *
 * Limit begrenzt einen Wert auf ein gegebenes Intervall.
 * @param value Der zu begrenzende Wert
 * @param lower_limit Untere Begrenzung
 * @param upper_limit Obere Begrenzung
 * @return Der begrenzte Wert
 */
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

/**
 * @brief PI Regler Instanz initialisieren.
 *
 * PI_Init initialisiert die Parameter des Reglers und setzt die Pointer fuer die
 * Eingangs- und Ausgangsgroessen auf die zu regelnden Groessen, die die jeweilige Instanz
 * nutzt.
 *
 * @param self Pointer auf eine Instanz der Klasse \ref reg_class_t
 * @param TA Abtastzeit des digitalen Reglers
 * @param kp Proportionalbeiwert des Reglers
 * @param ki Integralbeiwert des Reglers
 * @param ap Arbeitspunkt des Reglers bei Regelabweichung 0 und Integrationsanteil 0
 * @param lower_limit Untere Begrenzung des Reglerausgangs
 * @param upper_limit Obere Begrenzung des Reglerausgangs
 * @param y Pointer auf die zu regelnde Ausgangsgroesse
 * @param soll Pointer auf den Sollwert des Regelkreises
 * @param ist Pointer auf den Istwert des Regelkreises
 */
void reg_PI_Init(       reg_class_t *self,
                  const float        TA,
                  const float        kp,
                  const float        ki,
                  const float        ap,
                  const float        lower_limit,
                  const float        upper_limit,
                        float       *y,
                        float       *soll,
                        float       *ist            )
{
    int n;
    
    self->p.TA = TA;
    self->p.kp = kp;
    self->p.ki = ki;
    self->p.ki_x_TA = ki * TA;
    self->p.ap = ap;
    self->p.lower_limit = lower_limit;
    self->p.upper_limit = upper_limit;
    self->y    = y;
    self->soll = soll;
    self->ist  = ist;
    for( n=0; n<REG_STATEVARS; n ++ ) self->x[n] = 0.0;
}

/**
 * @brief Digitaler PI-Regler mit Anti Windup
 *
 * Digitaler PI-Regler mit Anti Windup Rueckfuehrung
 * @param self self Pointer auf eine Instanz der Klasse \ref reg_class_t
 * @return Ausgang des Reglers
 */
float reg_PI_Run( reg_class_t *self )
{
    /* x[0] : x Eingangsgroesse                 */
    /* x[2] : y Ausgangsgroesse ohne Begrenzung */
    /* x[3] : Anti Windup Rueckfuehrung         */
    
    self->x[0] =  *(self->soll) - *(self->ist);
    self->x[1] += self->p.ki_x_TA * self->x[0] - self->x[3];
    self->x[2] =  self->p.kp * self->x[0] + self->x[1] + self->p.ap;

    *(self->y) = reg_Limit( self->x[2], self->p.lower_limit, self->p.upper_limit );
    self->x[3] = self->x[2] - *(self->y);
    
    return( *(self->y) );
}

