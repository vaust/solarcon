#include <stdio.h>    
#include <stdlib.h>   
#include <getopt.h>
#include <asm/types.h>
#include <string.h>

#include "kbusapi.h"
#include "io.h"

int main( void )
{
	char inp_s[8];
	
	KbusOpen();
	printf( "(e)in bzw. (a)us:" );
	scanf( "%s", inp_s );
	if( inp_s[0] == 'e' ) {
		// pabOut_p->dout.sol_pu_sb = 0x01;
		SOL_PU_SB = IO_EIN;
	} 
	else {
		// pabOut_p->dout.sol_pu_sb = 0x00;
		SOL_PU_SB = IO_AUS;
	}  
	KbusUpdate();
	printf( "SOL_KOLL_T_MW = %5.1lf\n", toGradCelsius( SOL_KOLL_T_MW ) );
	printf( "SOL_SP1_Tu_MW = %5.1lf\n", toGradCelsius( SOL_SP1_Tu_MW ) );
	printf( "SOL_SP1_To_MW = %5.1lf\n", toGradCelsius( SOL_SP1_To_MW ) );
	/* */
	KbusClose();
	return -1;
}
