#ifndef _GEN_TYPES_H_
#define _GEN_TYPES_H_

/* <Defines> */
#define IO_EIN          0x01
#define IO_AUS          0x00
#define IO_AUF          0x01
#define IO_ZU           0x00

#define RESET           0x00
#define SET             0x01

#define MAX_Y_PCT       99.9
#define MIN_Y_PCT        0.1

#define ERR_OK             0
#define ERR_NOK           -1

#ifndef NULL
    #define NULL            ((void *)(0))
#endif
/* <Defines/> */

/* <Typen> */
typedef unsigned char   u8_t;
typedef signed char     s8_t;
typedef unsigned short  u16_t;
typedef signed short    s16_t;
typedef unsigned long   u32_t;
typedef signed long     s32_t;

typedef s16_t   temp10_pt1000_t;
typedef u8_t    di_bitbyte_t;

typedef s16_t   ao_0_10V_t;
typedef u8_t    do_bitbyte_t;

typedef s32_t   zeit_schaltpunkt_t;

/* Betriebszustaende, die sich fuer die einzelnen Heizkreise aus dem Zeitprogramm ergeben */
typedef enum { zAbgesenkt, zNormal } abgesenkt_t;
typedef enum { zAus, zEin } ein_aus_t;
typedef enum { zGesperrt, zFreigegeben } freigabe_t;
typedef enum { zNein, zJa } nutzzeit_t;
/* <Typen/> */

#endif /* _GEN_TYPES_H_ */

