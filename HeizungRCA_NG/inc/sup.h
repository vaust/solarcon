#ifndef _SUP_H_
#define _SUP_H_

#include "gen_types.h"

/* <Konstanten> */
#define SUP_REG_STATEVARS 4
/* <Konstanten/> */

/* <Typen> */
typedef struct sup_digreg_coeff_s {
    float TA;
    float kp;
    float ki;
    float ap;
    float lower_limit;
    float upper_limit;
} sup_digreg_coeff_t;

typedef struct sup_digreg_out_s {
    float y;                    /**< Stellgroesse zum Zeitpunkt t   */
    float x[SUP_REG_STATEVARS]; /**< Zustandsgroessen fuer Blockdarstellung des Anti Windup PI-Reglers */
} sup_digreg_out_t;

/* <Typen> */

/* <Prototypen> */
float sup_Limit( float *value, const float lower_limit, const float upper_limit );
void sup_DigRegInit( sup_digreg_coeff_t *q_p, 
                     sup_digreg_out_t   *y_p,
                     float               TA,
                     float               kp,
                     float               ki,
                     float               ap,
                     float               lower_limit,
                     float               upper_limit  );
float sup_DigRegler( const sup_digreg_coeff_t *q_p, 
                     const float               soll, 
                     const float               ist, 
                           sup_digreg_out_t   *y_p );
/* <Prototypen/> */

#endif /* _SUP_H_ */




