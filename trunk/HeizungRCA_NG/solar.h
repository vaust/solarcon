#ifndef _SOLAR_H_
#define _SOLAR_H_

/* <Defines> */
#define SOLAR_NORMAL           0
#define SOLAR_UEBERTEMPERATUR -1
/* <Defines/> */

/* <Typen> */
typedef struct {
    float koll_t_mw;
    float sp_t_max;
    float sp_to_mw;
    float sp_tu_mw;
    float dt_ein_sw;
    float dt_aus_sw;
} sol_in_t;
/* <Typen/> */

/* <Prototypen> */
void solar_Init( void );
int solar_Run(  const sol_in_t  *in_Sp1_p, 
                const sol_in_t  *in_Sp2_p, 
                      int       *sp1_av_sb_p, 
                      int       *sp2_av_sb_p,
                      int       *sol_pu_sb_p );
/* <Prototypen/> */

/* <lokale Protypen>  */
#ifdef _SOLAR_C_
int solar_Speicherabsperrventil( const sol_in_t *in_p, int *sp_av_sb_p );
void solar_Pumpe( const int *sp1_av_sb_p, const int *sp2_av_sb_p, int *sol_pu_sb_p );
#endif /* _SOLAR_C */
/* <lokale Protypen/> */ 

#endif /* _SOLAR_H_ */
