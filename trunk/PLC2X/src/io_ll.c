#define _IO_LL_C_

#include "gen_types.h"
#include "io_wago_hwif.h"
#include "io_pab_types.h"
#include "io_ll.h"

/**
 * @file io.c
 * @brief Interfacemethoden zum Lesen und Schreiben des Prozessabbildes
 * @author Volker Stegmann
 */


std_ret_t io_ll_read_Temperatur1( temperatur_t *data )
{
    *data = (temperatur_t) pabIn_p->ain.temperatur1 / 10.0;
    return E_OK;
}

std_ret_t io_ll_read_Temperatur2( temperatur_t *data )
{
    *data = (temperatur_t) pabIn_p->ain.temperatur2 / 10.0;
    return E_OK;
}

std_ret_t io_ll_read_Temperatur3( temperatur_t *data )
{
    *data = (temperatur_t) pabIn_p->ain.temperatur3 / 10.0;
    return E_OK;
}

std_ret_t io_ll_read_Temperatur4( temperatur_t *data )
{
    *data = (temperatur_t) pabIn_p->ain.temperatur4 / 10.0;
    return E_OK;
}

std_ret_t io_ll_read_DigitalIn1( di_bitbyte_t *data )
{
    *data = (do_bitbyte_t) pabIn_p->din.digitalIn1;
    return E_OK;
}

std_ret_t io_ll_read_DigitalIn2( di_bitbyte_t *data )
{
    *data = (do_bitbyte_t) pabIn_p->din.digitalIn2;
    return E_OK;
}

std_ret_t io_ll_read_DigitalIn3( di_bitbyte_t *data )
{
    *data = (do_bitbyte_t) pabIn_p->din.digitalIn3;
    return E_OK;
}

std_ret_t io_ll_read_DigitalIn4( di_bitbyte_t *data )
{
    *data = (do_bitbyte_t) pabIn_p->din.digitalIn1;
    return E_OK;
}

std_ret_t io_ll_read_Zaehler1( u16_t *data )
{
	*data =   ((u16_t) pabIn_p->ain.cnt1_msb << 8)
	        +  (u16_t) pabIn_p->ain.cnt1_lsb;
    return E_OK;
}

std_ret_t io_ll_read_Zaehler2( u16_t *data )
{
    *data =   ((u16_t) pabIn_p->ain.cnt2_msb << 8)
            +  (u16_t) pabIn_p->ain.cnt2_lsb;
    return E_OK;
}
