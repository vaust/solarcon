#ifndef _SUP_H_
#define _SUP_H_

#include "gen_types.h"

/* <Konstanten> */
#define REG_VFULLSCALE  0x8000
#define Q_MAXINDEX_EXP  2
#define Q_MAXINDEX      (1<<Q_MAXINDEX_EXP) /** immer Potenzen von 2 ! */
/* <Konstanten/> */

/* <Typen> */
typedef struct sup_digreg_coeff_s {
    float q[Q_MAXINDEX];
    float lower_limit;
    float upper_limit;
} sup_digreg_coeff_t;

typedef struct sup_digreg_out_s {
    float y[Q_MAXINDEX];        /**< Stellgroesse    zum Zeitpunkt t   */
    float xd[Q_MAXINDEX];       /**< Regelabweichung zum Zeitpunkt t-1 */
    u16_t t_index;              /**< aktueller Zeitindexzeiger auf Ringpuffer */
} sup_digreg_out_t;

/* <Typen> */

/* <Prototypen> */
float reg_Limit( float *value, const float lower_limit, const float upper_limit );
void reg_DigRegInit( sup_digreg_coeff_t *q_p, sup_digreg_out_t *y_p );
float reg_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, sup_digreg_out_t *y_p );
/* <Prototypen/> */

#endif /* _SUP_H_ */




