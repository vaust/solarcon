
#ifndef _IO_HL_H_
#define _IO_HL_H_

#define IO_MAX_TEMP    850.0
#define IO_MIN_TEMP   -100.0

#define IO_EPS           0.1

/* <Typen> */
/* </Typen> */

/* <Variablen> */
#ifdef _IO_HL_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/* <Prototypen> */
std_ret_t io_hl_InitZaehler( void );
/* </Prototypen> */

#endif /* _IO_V2_H_ */


