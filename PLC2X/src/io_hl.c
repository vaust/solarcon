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

#include <unistd.h>     /* Wird fuer sleep() Befehl benoetigt */

#ifdef __WAGO__
#include <asm/types.h>
#include "kbusapi.h"
#define KBUSUPDATE() KbusUpdate()
#else
#define KBUSUPDATE()
#endif

/**
 * \brief Wasserzaehler initialisieren
 */
static
std_ret_t io_hl_InitZaehlerKanal( cnt_t *steuer_p,
                             cnt_t *status_p  )
{
    s16_t       n;
    std_ret_t   ret;

    steuer_p->st.no_ueberlauf = 0;   /* Ueberlauf erlauben    */
    steuer_p->st.rueckwaerts  = 0;   /* vorwaerts zaehlen     */
    steuer_p->st.notused_a    = 0;   /* Immer 0               */
    steuer_p->st.setzen       = 0;   /* Noch nicht setzen     */
    steuer_p->st.sperren      = 0;   /* Zaehler nicht sperren */
    steuer_p->st.notused_b    = 0;   /* Immer 0               */
    KBUSUPDATE();
    sleep(1);

    steuer_p->lsb             = 0x00; /* Zaehler auf 0 setzen */
    steuer_p->msb             = 0x00;
    steuer_p->st.setzen       = 1;

    n = 16;                           /* Timeout falls setzen des Zaehler nicht klappt */
    do {
        KBUSUPDATE();
        sleep(1);
        n --;
        /* Warten bis Zaehlerstatus meldet: Gesetzt = 1 oder Timeout (n=0)*/
    } while( (status_p->st.setzen == 0) && (n > 0) );

    if( n > 0 ) {
        ret = E_OK;
        steuer_p->st.setzen      = 0;   /* Setzen wieder loeschen */
        KBUSUPDATE();
        sleep(1);
    }
    else {
        ret = E_NOK;
    }
    return ret;
}

std_ret_t io_hl_InitZaehler( void )
{
    std_ret_t ret;

    ret = io_hl_InitZaehlerKanal( &(pabOut_p->aout.cnt1_steuer),
                                  &(pabIn_p->ain.cnt1_status  )    );
    return ret;
}
