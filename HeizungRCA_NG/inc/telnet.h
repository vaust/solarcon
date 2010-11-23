#ifndef _TELNET_H_
#define _TELNET_H_

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
static void telnet_writeVars( const parse_set_t Vars[], int len, int fdesc, char *bufout );
static void telnet_writeAbsenk( int fdesc, char *bufout );
static void telnet_putVars( const parse_set_t Vars[], int len, int fdesc, char *bufout );
static void telnet_writeModuls( int fdesc, char *bufout );

#endif /* _TELNET_H_ */

