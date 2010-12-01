/** \file Messwert Verarbeitung mit Plausiblitaetspruefung
  * \author Volker Stegmann
  */

#define _IO_V2_C_

#define _IO_MASTER_ 

#include "gen_types.h"
#include "io_pab_types.h"
#include "io_wago_hwif.h"
#include "io_v2.h"

static  
void io_InitT( io_temp_obj_t     *self,
               float              messbereich_anfang,
               float              messbereich_ende,
               temp10_pt1000_t   *kbus_adresse_p     )
{
    self->messbereich_anfang = messbereich_anfang;
    self->messbereich_ende   = messbereich_ende;
    self->status             = io_Normal;
    self->kbus_adresse_p     = kbus_adresse_p;
}

static
void io_InitTall( void )
{
    io_InitT( &io_ALL_Tau_MW    , -50.0,  50.0, (temp10_pt1000_t *) &(pabIn_p->ain.all_tau_mw) );
    io_InitT( &io_SOL_KOLL_T_MW , -50.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_koll_t_mw) );
    io_InitT( &io_SOL_SP1_Tu_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp1_tu_mw) );
    io_InitT( &io_SOL_SP1_To_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp1_to_mw) );
    io_InitT( &io_SOL_SP2_Tu_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp2_tu_mw) );
    io_InitT( &io_SOL_SP2_To_MW ,   0.0, 150.0, (temp10_pt1000_t *) &(pabIn_p->ain.sol_sp2_to_mw) );
    io_InitT( &io_KES_Tvl_MW    ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.kes_tvl_mw) );
    io_InitT( &io_KES_Trl_MW    ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.kes_trl_mw) );
    io_InitT( &io_HK_Tvl_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.hk_tvl_mw) );
    io_InitT( &io_HK_Trl_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.hk_trl_mw) );
    io_InitT( &io_FB_PRIM_Trl_MW,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.fb_prim_trl_mw) );
    io_InitT( &io_FB_SEK_Tvl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.fb_sek_tvl_mw) );
    io_InitT( &io_WW_HZG_Tvl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_hzg_tvl_mw) );
    io_InitT( &io_WW_HZG_Trl_MW ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_hzg_trl_mw) );
    io_InitT( &io_WW_Tww_MW     ,   0.0, 100.0, (temp10_pt1000_t *) &(pabIn_p->ain.ww_tww_mw) );
}

/** \brief Methode zur Abfrage der Temperaturmessstellen.
  * Der Messwert wird in der Objektstruktur abgelegt und im Normalfall auch zur�ckgeben.
  * Bei unplausiblen Messwerten wird der rohe Messwert zur�ckgegeben und in der Objektstruktur
  * die jeweilige Messbereichsgrenze abgelegt, so dass noch sinnvoll weitergerechnet werden kann
  * \param self Pointer auf ein Temperaturmessobjekt
  */
io_obj_status_t io_ReadT( io_temp_obj_t *self, float *mw )
{
    float temp_val;

    switch( self->status ) {
        case io_ManuelleZuweisung:
            if( (void *)mw != NULL )
                *mw = self->messwert;
            /* Aus diesem Zustand kommt man nur durch Benutzerinteraktion (telnet.c) */
            break;
        case io_Normal:
            temp_val = TF(*(self->kbus_adresse_p));
            if( temp_val < IO_MIN_TEMP ) {
                self->status = io_Kurzschluss; 
                /* alten Messwert behalten */
            }
            else if( temp_val < self->messbereich_anfang ) {
                self->status = io_Unplausibel;
                self->messwert = self->messbereich_anfang; /* Messwert begrenzen */
            }
            else if( temp_val > IO_MAX_TEMP ) {
                self->status = io_Kabelbruch;
                /* alten Messwert behalten */
            }
            else if( temp_val > self->messbereich_ende ) {
                self->status = io_Unplausibel;
                self->messwert = self->messbereich_ende;   /* Messwert begrenzen */
            }
            else {
                /* Nur solange der Messwert in den Grenzen liegt bleibt der Zustand normal */
                self->status = io_Normal;  
                self->messwert = temp_val;
            }
            break;
        default:        
            temp_val = TF(*(self->kbus_adresse_p));
            if(    (temp_val >= self->messbereich_anfang)  
                && (temp_val <  self->messbereich_ende  ) ) {
                self->status = io_Normal;  /* Messwert liegt wieder in den normalen Grenzen */
                self->messwert = temp_val;
            }
            break;
    }
    
    if( (void *)mw != NULL )
        *mw = self->messwert;  /* Strukturwert in die Arbeitsvariable kopieren */
    return (self->status);
}

static
void io_InitY( io_ao10V_obj_t   *self, 
               float            stellbereich_anfang, 
               float            stellbereich_ende,
               io_obj_status_t  status,
               ao_0_10V_t       *kbus_adresse_p )
{
    self->stellbereich_anfang = stellbereich_anfang;
    self->stellbereich_ende   = stellbereich_ende;
    self->status              = io_Normal;
    self->kbus_adresse_p      = kbus_adresse_p;
}

static
void io_InitYall( void )
{
    io_InitY( &io_KES_Tvl_Y,    MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.kes_tvl_y)    );
    io_InitY( &io_HK_MV_Y,      MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.hk_mv_y)      );
    io_InitY( &io_FB_PRIM_MV_Y, MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.fb_prim_mv_y) );
    io_InitY( &io_WW_HZG_MV_Y,  MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.ww_hzg_mv_y)  );
    io_InitY( &io_WW_HZG_PU_Y,  MIN_Y_PCT, MAX_Y_PCT, io_Normal, (ao_0_10V_t *) &(pabOut_p->aout.ww_hzg_pu_y)  );
}

/** \brief Analogen Stellwert ausgeben mit Ueberpr�fung auf Plausibilitaet.
  * \param self Pointer auf Ausgabeobjekt 
  * \param val Auszugebender Wert 
  * Der Stellwert wird auf der PLC ausgegeben und im Feld stellwert abgelegt.
  * Weiterhin wird geprueft, ob der gewuenschte Stellwert im plausiblen Bereich liegt.
  */
io_obj_status_t io_WriteY( io_ao10V_obj_t *self, float val )
{
    self->stellwert = val;
    if( val < self->stellbereich_anfang ) {
        *(self->kbus_adresse_p) = (self->stellbereich_anfang *AO_FULLSCALE)/100;
        self->status            = io_Unterlauf;
    }
    else if( val > self->stellbereich_ende ) {
        *(self->kbus_adresse_p) = (self->stellbereich_ende   *AO_FULLSCALE)/100;
        self->status            = io_Ueberlauf;
    }
    else { /* Angeforderter Stellwert im plausiblen Bereich */
        *(self->kbus_adresse_p) = (val*AO_FULLSCALE)/100;
        self->status            = io_Normal;
    }
    
    return(self->status);
}

/** \brief Alle IO�s (Temperaturen und 0-10V Ausg�nge) initialisieren.
  */
void io_Init( void )
{
    io_InitYall();
    io_InitTall();
}

