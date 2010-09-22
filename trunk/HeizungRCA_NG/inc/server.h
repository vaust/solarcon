/* server.h */

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
void read_configfile( void );
/* </Prototypen> */

/* <Global> */
/* - Globale Threadvariablen -*/
pthread_t       threadlist[MAX_CON];
pthread_attr_t  threadattr;
int             next_thread = 0;
int             thread_args[2];

pthread_mutex_t	mutex;

static int      server_sock_fd, client_sock_fd;

/* </Global> */
