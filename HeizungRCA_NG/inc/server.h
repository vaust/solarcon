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
#define MAX_CON         0
#define MAX_NAME_LEN    6
#define MAX_STR_LEN     128

#define TCP_PORT        1969
// #define TCP_PORT        9691

/* </Konstanten> */

/* <Typen> */
/* </Typen> */

/* <Prototypen> */
void terminate( int sig );
void systimer_init( void );
/* </Prototypen> */

/* <Global> */
/* - Globale Threadvariablen - */
PUBLIC pthread_t       threadlist[MAX_CON];
PUBLIC pthread_attr_t  threadattr;
PUBLIC int             thread_args[2];
PUBLIC pthread_mutex_t mutex;
PUBLIC int             telnet_aktiv = RESET;

/* - Timer Variablen - */
// PUBLIC struct itimerval   timer; /**< Timer fuer zyklischen Aufruf von cntrl_run() */

/* - Socket Descriptoren - */
PUBLIC int      server_sock_fd, client_sock_fd;
/* </Global> */

#endif /* _SERVER_H_ */

