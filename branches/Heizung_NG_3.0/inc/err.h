/*
 *  SOLARCON Modular Solar Supported Home Heating Controller
 *  Copyright (C) 2011  Volker Stegmann
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
/** @brief Parameter der Fehlerkomponente */
typedef struct err_param_s {
    s16_t   br_TimeOut;
    float   dt;
} err_param_t;

/** @brief Eingangsgroessen der Fehlerkomponente */
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

/** @brief Ausgangsgroessen der Fehlerkomponente */
typedef struct err_out_s {
    s16_t           br_Countdown;              /**< Countdown bis Brenner gestartet haben muss */
    do_bitbyte_t    Sammelstoermeldung;        /**< Status der Sammelstoermeldungslampe        */
} err_out_t;

/** @brief Klassendefinition der Fehlerkomponente */
typedef struct err_class_s {
    err_param_t p;
    err_in_t    i;
    err_out_t   o;
} err_class_t;

/* <Typen/> */

/* <Prototypen> */
void err_Init( err_class_t *self );
void err_Run( err_class_t *self );
void err_Reset_Sammelstoermeldung( err_class_t *self );
void err_WriteInp( err_class_t *self, float        kes_tvl_sw,
                                      float        kes_tvl_mw,
                                      di_bitbyte_t br_RueckMeldung,
                                      di_bitbyte_t br_StoerMeldung,
                                      di_bitbyte_t stb_Fussbodenheizung,
                                      s16_t        tempsens_errcnt,
                                      s16_t        ao_errcnt,
                                      s16_t        sol_errcnt          );
/* <Prototypen/> */


#endif /* _ERR_H_ */

