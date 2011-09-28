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
 * @file sol.c
 * @brief Solarkreissteuerung fuer 2 Speicherkreise und einer Solarpumpe. Der Code ist auf weitere Speicherkreise
 * und weitere Pumpen skalierbar.
 * @author Volker Stegmann
 */

#define _SOL_C_

#include "sol.h"
#include "param.h"

void sol_Init( sol_class_t *self )
{
    self->p.sp_t_max  = param.sol.sp_t_max;
    self->p.dt_ein_sw = param.sol.dt_ein_sw;
    self->p.dt_aus_sw = param.sol.dt_aus_sw;
    self->p.TA        = MSEC2SEC(param.sys.zykluszeit);
    self->sol_wz      = 0.0;
}

/**
 * @brief Solarspeicherabsperrventil entsprechend der Temperaturdifferenzen
 * zwischen Speicher und Kollektor betaetigen.
 *
 * @param par_p[in] Parametrisierung
 * @param koll_t_mw[in] Vorlauftemperatur des speisenden Kollektors
 * @param t_sp_p[in] Pointer auf Struktur mit oberer und unterer Kollektortemperatur
 * @param sp_av_sb_p[out] Zustand des Absperrventils (offen/geschlossen)
 * @return Fehlercode z.B Speicheruebertemperatur: Die Speicher koennen die Waerme nicht
 *         mehr aufnehmen
 */
static 
int sol_Speicherabsperrventil( const sol_param_t   *par_p, 
                               const float         koll_t_mw,
                               const sol_sp_t_mw_t *t_sp_p,  
                                     do_bitbyte_t  *sp_av_sb_p )
{
    int errorcode;

    if( t_sp_p->to_mw < par_p->sp_t_max ) {
        /* Die Kollektortemperatur liegt unter dem Maximalwert  */
        if( koll_t_mw > ( t_sp_p->tu_mw + par_p->dt_ein_sw ) ) {
            *sp_av_sb_p  = IO_AUF;
        }
        else {
            if( koll_t_mw <= ( t_sp_p->tu_mw + par_p->dt_aus_sw ) ) {
                *sp_av_sb_p  = IO_ZU;
            }
            else {
                *sp_av_sb_p  = IO_AUF;
            }
        }
        errorcode = SOL_NORMAL;
    }
    else {
        /* Die Kollektortemperatur liegt ueber dem Maximalwert  */
        *sp_av_sb_p  = IO_ZU;
        errorcode = SOL_UEBERTEMPERATUR;
    }
    return( errorcode );
}

/**
 * @brief Kollektorpumpe(n) einschalten.
 *
 * Die Pumpe eines Kollektors einschalten, wenn mind. 1 Ventil zum Speicher offen ist.
 * @param out_p Eingangsgroeßen Ventilstellung, Ausgangsgroeßen Pumpe ein/aus
 * @return kein
 */
static 
void sol_Pumpe( sol_out_t *out_p )
{
    if( ( out_p->av_sb[SP1] == IO_ZU ) &&
        ( out_p->av_sb[SP2] == IO_ZU )    ) {
        out_p->pu_sb[KO1] = IO_AUS;
    }
    else {
        out_p->pu_sb[KO1] = IO_EIN;
    }
}

/**
 * @brief Waermezaehler
 *
 * Diese Methode implementiert einen einfachen Algorithmus zur Abschaetzung der
 * vom Solarkollektor an die Speicher gelieferte Waermemenge.
 *
 * @param self Pointer auf Instanz der Klasse sol_class_t
 */
void sol_Wz( sol_class_t *self )
{
    float akt_P; /* aktuelle Leistungsabgabe an den Speicher Speicher 1, 2 */
    s16_t i;

    for( i=0; i<SOL_N_SP; i++ ) {
        if( self->o.av_sb[i] == IO_AUF ) {
            akt_P = self->p.k_wlf * ( self->i.koll_t_mw[KO1] - self->i.t_sp[i].tu_mw );
            self->sol_wz += akt_P * self->p.TA;
        }
    }
}


/**
 * @brief eigentlicher Solarregler.
 *
 * Absperrventile steuern und die Pumpen entsprechend betaetigen.
 * @param self Pointer auf Instanz der Klasse sol_class_t
 * @return Fehlercode fuer Sammelstoerungsauswertung.
 */
s16_t sol_Run( sol_class_t *self )
{
    s16_t errorcode = 0;

    /* Absperrventil Speicher 1 */
    errorcode += sol_Speicherabsperrventil( &(self->p), self->i.koll_t_mw[KO1],
                                                        &(self->i.t_sp[SP1]),
                                                        &(self->o.av_sb[SP1]) );
    /* Absperrventil Speicher 2 */
    errorcode += sol_Speicherabsperrventil( &(self->p), self->i.koll_t_mw[KO1],
                                                        &(self->i.t_sp[SP2]),
                                                        &(self->o.av_sb[SP2]) );
    /* Pumpe entsprechend des Absperrventilzustands schalten */
    sol_Pumpe( &(self->o) );

    return( errorcode );
}

/**
 * @brief Befuellen des Eingangsvektors
 *
 * @param koll_t_mw[in] Kollektortemperatur
 * @param sp1_to_mw[in] Obere Temperatur des Speicher 1
 * @param sp1_tu_mw[in] Untere Temperatur des Speicher 1
 * @param sp2_to_mw[in] Obere Temperatur des Speicher 2
 * @param sp2_tu_mw[in] Untere Temperatur des Speicher 2
 */
void sol_WriteInp(       sol_class_t *self,
                   const float     koll_t_mw,
                   const float     sp1_to_mw,
                   const float     sp1_tu_mw,
                   const float     sp2_to_mw,
                   const float     sp2_tu_mw )
{
    self->i.koll_t_mw[KO1]  = koll_t_mw;
    self->i.t_sp[SP1].to_mw = sp1_to_mw;
    self->i.t_sp[SP1].tu_mw = sp1_tu_mw;
    self->i.t_sp[SP2].to_mw = sp2_to_mw;
    self->i.t_sp[SP2].tu_mw = sp2_tu_mw;
}




