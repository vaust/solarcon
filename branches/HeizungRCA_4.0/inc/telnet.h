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

/** \file Prototypen fuer lokale telnet Funktionen 
  * \author Volker Stegmann
  */

#ifndef _TELNET_H_
#define _TELNET_H_

/* Typen */
#ifdef _TELNET_C_

typedef struct telnet_HAND_DecisionTableEntry_s {
	char*	modName;
	int     modNameLen;
	u8_t* 	flagp;
	char*	statustext;
} telnet_HAND_DecisionTableEntry_t;

typedef struct telnet_PUT_DecisionTableEntry_s {
    char*           modName;
    int             modNameLen;
    parse_set_t*    modVarsp;
} telnet_PUT_DecisionTableEntry_t;

typedef struct telnet_;
#endif // _TELNET_C_
	
/* Prototpyen */
void *telnet_Task( void *arg );

#ifdef _TELNET_C_
static void telnet_writeT( int fdesc, char *bufout );
static void telnet_writeAO( int fdesc, char *bufout );
static void telnet_writeDI( int fdesc, char *bufout );
static void telnet_writeDO( int fdesc, char *bufout );
static void telnet_writeSW( int fdesc, char *bufout );
static void telnet_writeFB( int fdesc, char *bufout );
static void telnet_writeSOL( int fdesc, char *bufout );
static void telnet_writeHK( int fdesc, char *bufout );
static void telnet_writeWW( int fdesc, char *bufout );
static void telnet_writeVorgabenparameter( int fdesc, char *bufout );
static void telnet_parseGet( int fdesc, char *bufout );
static void telnet_writeSchaltzeiten( int fdesc, char *bufout );
static void telnet_writeHelp( int fdesc, char *bufout );
static void telnet_writeAbsenk( int fdesc, char *bufout );
static void telnet_writeVars( const parse_set_t Vars[], const int len, int fdesc, char *bufout );
static void telnet_putVars( const parse_set_t Vars[], const int len, int fdesc, char *bufout );
static void telnet_writeModuls( int fdesc, char *bufout );
static void telnet_InitModules( void );
static void telnet_PrintModVersion( int fdesc, char *bufout );
#endif /* _TELNET_C_ */

#endif /* _TELNET_H_ */

