#ifndef _SUP_H_
#define _SUP_H_

/* <Konstanten> */
#define VFULLSCALE 0x8000
/* <Konstanten/> */

/* <Typen> */
typedef struct {
    float q0;
    float q1;
    float lower_limit;
    float upper_limit;
} sup_digreg_coeff_t;
/* <Typen> */

/* <Prototypen> */
float sup_Limit( float *value, const float lower_limit, const float upper_limit );
float sup_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, float *y );
/* <Prototypen/> */

#endif /* _SUP_H_ */




