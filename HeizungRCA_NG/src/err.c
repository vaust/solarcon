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

/**
 *  @file err.c
 *  @author Volker Stegmann
 *  @brief Fehlerbehandlungsmodul.
 *
 *  Hiermit werden alle moeglichen Fehlerereignisse gesammelt und nach entsprechender
 *  Wichtung die Sammelstoermeldung gesetzt.
 *  SAMMELSTOERMELDUNG =
 *        Kollektoruebertemperatur
 *  oder  Brennermeldung kommt nicht nach max 1 min nach Anforderung
 *  oder  Kesselstoermeldung ist gesetzt
 *  oder  STB der Fussbodenheizung hat ausgeloest
 *  oder  ...
 */

#define _ERR_C_

#include "gen_types.h"
#include "param.h"
#include "err.h"

/**
 * @brief Fehlerkomponente initialisieren
 *
 * @param self Pointer auf Instanz der Klasse err_class_t
 */
void err_Init( err_class_t *self )
{
    self->p.br_TimeOut   = 480;                       /* 480 entspr. bei 0.5sec Zyklus 4min       */
    self->p.dt           = param_kes_sp_dt_sw / 2.0;  /* Tvl_MW muss um diesen Betrag hoeher sein */

    self->o.br_Countdown = self->p.br_TimeOut;
    
    self->i.sol_errcnt      = 0;  /* Zaehler auf 0 -> kein Fehler                */
    self->i.ao_errcnt       = 0;  /* Jedes Fehlerereignis zaehlt Fehler herunter */
    self->i.tempsens_errcnt = 0;
    self->i.common_errcnt   = 0;
}

/** 
 * \brief Betriebszustaende lesen und auf Plausibiliteat pruefen.
 * Falls nicht plausibel: Sammelstoermeldung setzen
 */
void err_Run( err_class_t *self )
{
    if( self->i.kes_tvl_sw > (self->i.kes_tvl_mw + self->p.dt) ) {
        if( self->i.br_RueckMeldung == RESET ) {
            if( self->o.br_Countdown > 0 ) self->o.br_Countdown --;
        }
        else {
            self->o.br_Countdown = self->p.br_TimeOut;
        }
    }
    else {
        self->o.br_Countdown = self->p.br_TimeOut;
    }

    if(    (0          == self->o.br_Countdown        )
        || (SET        == self->i.br_StoerMeldung     )
        || (SET        == self->i.stb_Fussbodenheizung)
//        || (ERR_MAXCNT >  self->i.sol_errcnt          )
//        || (ERR_MAXCNT >  self->i.tempsens_errcnt     )
        || (ERR_MAXCNT >  self->i.ao_errcnt           )
//        || (0          >  self->i.common_errcnt       )
      ) {
        self->o.Sammelstoermeldung = SET;
    }
    else {
        self->o.Sammelstoermeldung = RESET;
    }
}

/**
 * \brief Sammelstoermeldung zuruecksetzen.
 *
 * Dies Funktion soll vom Benutzerinterface aufgerufen werden.
 * \param par_p[in] enthaelt timeout fuer Anforderungscountdown
 * \param out_p[out] Stoermeldung zuruecksetzen.
 */
void err_Reset_Sammelstoermeldung( err_class_t *self )
{
    self->o.br_Countdown       = self->p.br_TimeOut;
    self->o.Sammelstoermeldung = RESET;
    self->i.sol_errcnt          = 0;
    self->i.tempsens_errcnt     = 0;
    self->i.ao_errcnt           = 0;
    self->i.common_errcnt       = 0;
}

/*
void err_WriteInp( err_in_t *in_p, float        kes_tvl_sw,
                                   float        kes_tvl_mw,
                                   di_bitbyte_t br_RueckMeldung,
                                   di_bitbyte_t br_StoerMeldung,
                                   di_bitbyte_t stb_Fussbodenheizung,
                                   s16_t        tempsens_errcnt,
                                   s16_t        ao_errcnt,
                                   s16_t        sol_errcnt          )
{
    self->i.kes_tvl_sw           = kes_tvl_sw;
    self->i.kes_tvl_mw           = kes_tvl_mw;
    self->i.br_RueckMeldung      = br_RueckMeldung;
    self->i.br_StoerMeldung      = br_StoerMeldung;
    self->i.stb_Fussbodenheizung = stb_Fussbodenheizung;
    self->i.tempsens_errcnt      = tempsens_errcnt;
    self->i.ao_errcnt            = ao_errcnt;
    self->i.sol_errcnt           = sol_errcnt;
}
*/

