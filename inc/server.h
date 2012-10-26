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

#ifndef _SERVER_H_
#define _SERVER_H_

/* <Makros> */
#undef PUBLIC
#ifdef _SERVER_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/* </Makros> */

/* <Konstanten> */
#define MAX_CON         1
#define MAX_NAME_LEN    6
#define MAX_STR_LEN     128

#define TCP_PORT        1969
// #define TCP_PORT        9691

/* </Konstanten> */

/* <Typen> */
/* </Typen> */

/* <Prototypen> */
void terminate( int sig );
void systimer_init( u32_t zykluszeit );
/* </Prototypen> */

/* <Global> */
/* - Globale Threadvariablen - */
PUBLIC pthread_t       thread;
PUBLIC pthread_attr_t  threadattr;
PUBLIC int             thread_args[2];
PUBLIC pthread_mutex_t mutex;
PUBLIC int             next_thread;

/* - Timer Variablen - */
PUBLIC struct itimerval   timer; /**< Timer fuer zyklischen Aufruf von cntrl_run() */

/* - Socket Descriptoren - */
PUBLIC int      server_sock_fd, client_sock_fd;
/* </Global> */

#endif /* _SERVER_H_ */

