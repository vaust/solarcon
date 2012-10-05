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

#ifndef _MAIN_H_
#define _MAIN_H_

/* <Makros> */
#undef PUBLIC
#ifdef _MAIN_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif
/* </Makros> */


/* <Konstanten> */
/* </Konstanten> */

/* <Typen> */
/* </Typen> */

/* <Prototypen> */
void terminate( int sig );
void systimer_init( u32_t zykluszeit );
/* </Prototypen> */

/* <Global> */
/** @brief Mutex Objekt */
PUBLIC pthread_mutex_t mutex;

/** @brief Timer Variablen - */
PUBLIC struct itimerval   timer; /**< Timer fuer zyklischen Aufruf von test_run() */
/* </Global> */

#endif /* _MAIN_H_ */

