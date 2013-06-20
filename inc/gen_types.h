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

#ifndef NULL
    #define NULL            ((void *)(0L))
#endif

#define STD_ERR           -1

/* <Defines/> */

/* <Typen> */
typedef unsigned char   u8_t;
typedef signed char     s8_t;
typedef unsigned short  u16_t;
typedef signed short    s16_t;
typedef unsigned long   u32_t;
typedef signed long     s32_t;

typedef s16_t   temp10_pt1000_t;     /**< @brief Temperatur eines PT1000 Sensors in 0.1 Grad */
typedef u8_t    di_bitbyte_t;        /**< @brief Digitaler Schaltzustand eines Eingangs */

typedef s16_t   ao_0_10V_t;          /**< @brief Analogstellgroesse */
typedef u8_t    do_bitbyte_t;        /**< @brief Digitaler Schaltzustand eines Ausgangs */

/**
 * @brief Datenstruktur fuer Zählerklemme. Achtung: Belegt nicht Digitaleingaenge, sondern Analogeingaenge und
 * -Ausgaenge !! Eingaenge sind Statusbyte und Zaehlerstaende, Ausgaenge sind Steuerbyte und Zaehlerinitialisierung
 */
typedef struct cnt_status_steuer_s {
    u8_t    no_ueberlauf : 1;
    u8_t    rueckwaerts  : 1;
    u8_t    notused_a    : 2;
    u8_t    sperren      : 1;
    u8_t    setzen       : 1;
    u8_t    notused_b    : 2;
} cnt_status_steuer_t;

typedef struct cnt_s {
    cnt_status_steuer_t st;
    u8_t    lsb;        /**< LSB des Zaehlerwertes */
    u8_t    msb;        /**< MSB des Zählerwertes  */
} cnt_t;


typedef s32_t   zeit_schaltpunkt_t;  /**< @brief Zeitpunkt eines Wochentags in Minuten seit Sonntag 0:00 Uhr */

/* Betriebszustaende, die sich fuer die einzelnen Heizkreise aus dem Zeitprogramm ergeben */
typedef enum abgesenkt_e { zAbgesenkt, zNormal } abgesenkt_t;
typedef enum ein_aus_e { zAus, zEin } ein_aus_t;
typedef enum freigabe_e { zGesperrt, zFreigegeben } freigabe_t;
typedef enum nutzzeit_e { zNein, zJa } nutzzeit_t;
/* <Typen/> */

#endif /* _GEN_TYPES_H_ */

