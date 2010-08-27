#ifndef SUP_H
#define SUP_H

/* <Typen> */
typedef struct {
    float q0;
    float q1;
    float lower_limit;
    float upper_limit;
} sup_digreg_coeff_t;
/* <Typen> */

/* <Prototypen> */
void sup_Limit( float *value, const float lower_limit, const float upper_limit );
float sup_DigRegler( const sup_digreg_coeff_t *q_p, const float soll, const float ist, float *y );
/* <Prototypen/> */

#endif /* SUP_H */