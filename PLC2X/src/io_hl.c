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

/** \file io_v2.c
 *  \brief Messwert Verarbeitung mit Plausiblitaetspruefung.
 *  \author Volker Stegmann
 */

#define _IO_HL_C_

/** Dient zur Konfiguration welche Variante von IO (io.c oder io_v2.c) auf die HW zugreift */
#define _IO_MASTER_ 

#define __DEBUG__
#include <stdio.h>

#include "gen_types.h"
#include "io_pab_types.h"
#include "io_wago_hwif.h"
#include "io_hl.h"

// #include <unistd.h>     /* Wird fuer sleep() Befehl benoetigt */

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#define KBUSUPDATE() KbusUpdate()
#else
#define KBUSUPDATE()
#endif

/**
 * @brief Wasserzaehler initialisieren
 */
std_ret_t io_hl_InitZaehlerKanal1( void )
{
    s16_t       n;
    std_ret_t   ret;
    cnt_status_steuer_t *status_p;
    cnt_status_steuer_t *steuer_p;

    steuer_p = (cnt_status_steuer_t *) &(pabOut_p->aout.cnt2_steuer);
    status_p = (cnt_status_steuer_t *) &(pabIn_p->ain.cnt2_status);

    steuer_p->no_ueberlauf = 0;   /* Ueberlauf erlauben    */
    steuer_p->rueckwaerts  = 0;   /* vorwaerts zaehlen     */
    steuer_p->notused_a    = 0;   /* Immer 0               */
    steuer_p->setzen       = 0;   /* Noch nicht setzen     */
    steuer_p->sperren      = 0;   /* Zaehler nicht sperren */
    steuer_p->notused_b    = 0;   /* Immer 0               */
    KBUSUPDATE();
    sleep(1);

    pabOut_p->aout.cnt2_lsb = 0x00; /* Zaehler auf 0 setzen */
    pabOut_p->aout.cnt2_msb = 0x00;
    steuer_p->setzen        = 1;

    n = 8;                           /* Timeout falls setzen des Zaehler nicht klappt */
    do {
        KBUSUPDATE();
        sleep(1);
        n --;
        /* Warten bis Zaehlerstatus meldet: Gesetzt = 1 oder Timeout (n=0)*/
    } while( (status_p->setzen == 0) && (n > 0) );

    if( n > 0 ) {
        ret = E_OK;
        steuer_p->setzen = 0;   /* Setzen wieder loeschen */
        KBUSUPDATE();
        sleep(1);
    }
    else {
        ret = E_NOK;
    }
    return ret;
}

/**
 * @brief Zaehlerinitialisierung fuer beide Kanaele
 */

std_ret_t io_hl_InitZaehler( u8_t *base )
{
	return E_NOK;
}


