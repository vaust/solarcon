#ifndef _IO_LL_H_
#define _IO_LL_H_

#include "gen_types.h"

/* <Prototypen> */

std_ret_t io_ll_read_Temperatur1( temperatur_t *data );    /**<  */
std_ret_t io_ll_read_Temperatur2( temperatur_t *data );    /**<  */
std_ret_t io_ll_read_Temperatur3( temperatur_t *data );    /**<  */
std_ret_t io_ll_read_Temperatur4( temperatur_t *data );    /**<  */
std_ret_t io_ll_read_DigitalIn1( di_bitbyte_t *data );     /**<  */
std_ret_t io_ll_read_DigitalIn2( di_bitbyte_t *data );     /**<  */
std_ret_t io_ll_read_DigitalIn3( di_bitbyte_t *data );     /**<  */
std_ret_t io_ll_read_DigitalIn4( di_bitbyte_t *data );     /**<  */
std_ret_t io_ll_read_Zaehler1LSB( u8_t *data );            /**<  */
std_ret_t io_ll_read_Zaehler1MSB( u8_t *data );            /**<  */
std_ret_t io_ll_read_Zaehler1( u16_t *data );              /**<  */

/* <Prototypen/> */
#endif /* _IO_LL_H_ */



