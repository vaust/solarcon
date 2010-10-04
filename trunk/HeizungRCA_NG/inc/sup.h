#ifndef _SUP_H_
#define _SUP_H_

#include "gen_types.h"

/* <Konstanten> */
#define VFULLSCALE 0x8000
/* <Konstanten/> */

/* <Typen> */
typedef struct {
    float q0;
    float q1;
    float antiwup;
    float lower_limit;
    float upper_limit;
} sup_digreg_coeff_t;

typedef struct {
    float y;            /**< Stellgroesse    zum Zeitpunkt t   */
    float y_1;          /**< Stellgroesse    zum Zeitpunkt t-1 */
    float xd_1;         /**< Regelabweichung zum Zeitpunkt t-1 */
} sup_digreg_out_t;

/* <Typen> */

/* <Prototypen> */
float sup_Limit( float *value, const float lower_limit, const float upper_limit );
void sup_DigRegInit( sup_digreg_coeff_t *q_p, sup_digreg_out_t *y_p );
float sup_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, sup_digreg_out_t *y_p );
/* <Prototypen/> */

#endif /* _SUP_H_ */




