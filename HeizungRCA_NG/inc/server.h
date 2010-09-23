#ifndef _TELNET_H_
#define _TELNET_H_

/* <Makros> */
#ifdef _SERVER_C_
    #define PUBLIC
#else
    #define PUBLIC extern
#endif

/* </Makros> */

/* <Konstanten> */
#define MAX_CON         3
#define MAX_NAME_LEN    6
#define MAX_STR_LEN     128

#define TCP_PORT        1969
/* </Konstanten> */

/* <Typen> */
/* </Typen> */

/* <Prototypen> */
int create_server_sock( int port );
void terminate( int sig );
void *server_thread( void *arg );
extern void *cntrl_thread( void *arg );
void *telnet_thread( void *arg );

#ifdef _TELNET_C_
void telnet_writeT( int fdesc, char *bufout );
void telnet_writeAO( int fdesc, char *bufout );
void telnet_writeDI( int fdesc, char *bufout );
void telnet_writeDO( int fdesc, char *bufout );
void telnet_writeFB( int fdesc, char *bufout );
void telnet_writeSOL( int fdesc, char *bufout );
void telnet_writeHK( int fdesc, char *bufout );
void telnet_writeVorgabenparameter( int fdesc, char *bufout );
void telnet_parseGet( int fdesc, char *bufout );
void telnet_parsePut( int fdesc, char *bufout );
void telnet_writeHelp( int fdesc, char *bufout );
#endif
/* </Prototypen> */

/* <Global> */
/* - Globale Threadvariablen -*/
PUBLIC pthread_t       threadlist[MAX_CON];
PUBLIC pthread_attr_t  threadattr;
PUBLIC int             thread_args[2];
PUBLIC pthread_mutex_t mutex;

#ifdef _SERVER_C_
int             next_thread=0;
#else 
extern int      next_thread;
#endif

PUBLIC int             server_sock_fd, client_sock_fd;

/* </Global> */

#endif

