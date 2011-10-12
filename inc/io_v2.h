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

#ifndef _IO_V2_H_
#define _IO_V2_H_

#define IO_MAX_TEMP    850.0
#define IO_MIN_TEMP   -100.0

#define IO_EPS           0.1

/* <Typen> */
typedef enum io_obj_status_e { io_Normal,             /**< Sensor-/Aktorwert ist innerhalb der Messbereichsgrenzen und gueltig */
                               io_Kabelbruch,         /**< Es liegt eine Kabelbruch vor */
                               io_Kurzschluss,        /**< Der Sensor/Aktor ist kurzgeschlossen */
                               io_Unplausibel,        /**< Der Wert ist unplausibel */
                               io_Ueberlauf,          /**< Der Wert ist zu gross */
                               io_Unterlauf,          /**< Der Wert ist zu klein */
                               io_AllgemeinerFehler,  /**< Es liegt ein allgemeiner, nicht naeher spezifizierter Fehler vor */
                               io_ManuelleZuweisung   /**< Der Mess-/Stellwert kann in der Diagnose manuell zugewiesen werden */
                              } io_obj_status_t;

typedef struct io_tempsens_obj_s {
    float           messbereich_anfang;
    float           messbereich_ende;
    float           messwert;
    io_obj_status_t status;
    temp10_pt1000_t *kbus_adresse_p;
} io_temp_obj_t;

typedef struct io_ao10V_obj_s {
    float           stellbereich_anfang;
    float           stellbereich_ende;
    float           stellwert;
    io_obj_status_t status;
    ao_0_10V_t      *kbus_adresse_p;
} io_ao10V_obj_t;
    
typedef struct io_digin_obj_s {
    di_bitbyte_t    messwert;
    io_obj_status_t status;
} io_digin_obj_t;
    
/* </Typen> */

/* <Variablen> */
#ifdef _IO_V2_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif
/* Temperaturmesswertobjekte */
PUBLIC io_temp_obj_t    io_ALL_Tau_MW;
PUBLIC io_temp_obj_t    io_SOL_KOLL_T_MW;
PUBLIC io_temp_obj_t    io_SOL_SP1_Tu_MW;
PUBLIC io_temp_obj_t    io_SOL_SP1_To_MW;
PUBLIC io_temp_obj_t    io_SOL_SP2_Tu_MW;
PUBLIC io_temp_obj_t    io_SOL_SP2_To_MW;
PUBLIC io_temp_obj_t    io_KES_Tvl_MW;
PUBLIC io_temp_obj_t    io_KES_Trl_MW;
PUBLIC io_temp_obj_t    io_HK_Tvl_MW;
PUBLIC io_temp_obj_t    io_HK_Trl_MW;
PUBLIC io_temp_obj_t    io_FB_PRIM_Trl_MW;
PUBLIC io_temp_obj_t    io_FB_SEK_Tvl_MW;
PUBLIC io_temp_obj_t    io_WW_HZG_Tvl_MW;
PUBLIC io_temp_obj_t    io_WW_HZG_Trl_MW;
PUBLIC io_temp_obj_t    io_WW_Tww_MW;

/* Analogstellwertobjekte */
PUBLIC io_ao10V_obj_t   io_KES_Tvl_Y;
PUBLIC io_ao10V_obj_t   io_HK_MV_Y;
PUBLIC io_ao10V_obj_t   io_FB_PRIM_MV_Y;
PUBLIC io_ao10V_obj_t   io_WW_HZG_MV_Y;
PUBLIC io_ao10V_obj_t   io_WW_HZG_PU_Y;
/* </Variablen> */

/* <Prototypen> */
void io_Init( void );

io_obj_status_t io_ReadT( io_temp_obj_t *this, float *mw );
io_obj_status_t io_WriteY( io_ao10V_obj_t *this, float val );
/* </Prototypen> */

#endif /* _IO_V2_H_ */


