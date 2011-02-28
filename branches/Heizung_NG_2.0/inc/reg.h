#ifndef _REG_H_
#define _REG_H_

#include "gen_types.h"

/* <Konstanten> */
#define REG_STATEVARS 4
/* <Konstanten/> */

/* <Typen> */
typedef struct reg_par_s {
    float TA;
    float kp;
    float ki;
    float ap;
    float lower_limit;
    float upper_limit;
} reg_par_t;

typedef struct reg_class_s {
    reg_par_t   p;                    /**< Parametersatz des PI-Reglers   */
    float       y;                    /**< Stellgroesse zum Zeitpunkt t   */
    float       soll;                 /**< Sollwert zum Zeitpunkt t       */
    float       ist;                  /**< Istwert zum Zeitpunkt t        */
    float       x[SUP_REG_STATEVARS]; /**< Zustandsgroessen fuer Blockdarstellung des Anti Windup PI-Reglers */
} reg_class_t;

/* <Typen> */

/* <Prototypen> */
float reg_Limit( float value, const float lower_limit, const float upper_limit );
void reg_PI_Init(       reg_class_t *self,
                  const float        TA,
                  const float        kp,
                  const float        ki,
                  const float        ap,
                  const float        lower_limit,
                  const float        upper_limit  );

float reg_PI_Run( reg_class_t *self );
/* <Prototypen/> */

#endif /* _SUP_H_ */




