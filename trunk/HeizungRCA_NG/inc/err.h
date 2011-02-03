#ifndef _ERR_H_
#define _ERR_H_

#include "gen_types.h"

/* <Defines> */
#define ERR_OK             0
#define ERR_NOK           -1
/** Jeder Fehlerzaehler darf maximal 5 Fehler zaehlen ehe eine Stoerung
 * gemeldet wird
 */
#define ERR_MAXCNT        -5

/* <Defines/> */

/* <Typen> */
typedef struct err_param_s {
    s16_t   br_TimeOut;
    float   dt;
} err_param_t;


typedef struct err_in_s {
    float           kes_tvl_sw;
    float           kes_tvl_mw;
    di_bitbyte_t    br_RueckMeldung;           /**< Rueckmeldung vom Brenner (Prozesssignal)             */
    di_bitbyte_t    br_StoerMeldung;           /**< Brennerstoermeldung      (Prozesssignal)             */
    di_bitbyte_t    stb_Fussbodenheizung;      /**< Sicherheitstemperaturschalter FB-Hzg (Prozesssignal) */
    s16_t           tempsens_errcnt;           /**< Fehlerzaehler fuer Temperatursensoren                */
    s16_t           ao_errcnt;                 /**< Fehlerzaehler fuer Analog 0-10V Ausgabe              */
    s16_t           sol_errcnt;                /**< Fehlerzaehler fuer Solarregler                       */
    s16_t           common_errcnt;             /**< Fehlerzaehler fuer allgemeine Fehler                 */
} err_in_t;


typedef struct err_out_s {
    s16_t           br_Countdown;              /**< Countdown bis Brenner gestartet haben muss */
    do_bitbyte_t    Sammelstoermeldung;        /**< Status der Sammelstoermeldungslampe        */
} err_out_t;
/* <Typen/> */

/* <Prototypen> */
void err_Init( err_param_t *par_p, 
               err_in_t    *in_p, 
               err_out_t   *out_p );

void err_Run( const err_param_t *par_p,
              const err_in_t    *in_p,
                    err_out_t   *out_p );

void err_Reset_Sammelstoermeldung( err_param_t *par_p,
                                   err_in_t    *in_p,
                                   err_out_t   *out_p );

void err_WriteInp( err_in_t *in_p, float        kes_tvl_sw,
                                   float        kes_tvl_mw,
                                   di_bitbyte_t br_RueckMeldung,
                                   di_bitbyte_t br_StoerMeldung,
                                   di_bitbyte_t stb_Fussbodenheizung,
                                   s16_t        tempsens_errcnt,
                                   s16_t        ao_errcnt,
                                   s16_t        sol_errcnt          );
/* <Prototypen/> */


#endif /* _ERR_H_ */

