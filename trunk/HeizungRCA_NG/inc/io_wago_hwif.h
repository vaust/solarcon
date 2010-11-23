#ifndef _IO_WAGO_HWIF_H_
#define _IO_WAGO_HWIF_H_

#include "io_pab_types.h"
/*
 *   PAB In:         00ffe060         PAB Size: 2040 bytes
 *   PAB Out:        00ffe858         PAB Size: 2040 bytes
*/

#define PAB_IN  ((volatile Control_Input_t  *) 0xFFE060)
#define PAB_OUT ((volatile Control_Output_t *) 0xFFE858)

#ifdef __WAGO__

#ifdef _IO_MASTER_
volatile Control_Output_t * const pabOut_p = PAB_OUT;
volatile Control_Input_t  * const pabIn_p  = PAB_IN;
#else
extern volatile Control_Output_t * const pabOut_p;
extern volatile Control_Input_t  * const pabIn_p; 
#endif /* _IO_MASTER_ */

#else /* __WAGO__ */

#ifdef _IO_MASTER_
volatile Control_Output_t         pab_Dbg_Out;
volatile Control_Input_t          pab_Dbg_In;

volatile Control_Output_t * const pabOut_p = &pab_Dbg_Out;
volatile Control_Input_t  * const pabIn_p  = &pab_Dbg_In;
#else
extern volatile Control_Output_t         pab_Dbg_Out;
extern volatile Control_Input_t          pab_Dbg_In;

extern volatile Control_Output_t * const pabOut_p;         
extern volatile Control_Input_t  * const pabIn_p;  
#endif /* _IO_MASTER_ */

#endif /* __WAGO__ */

#define AO_FULLSCALE    0x8000

#else
#error "io_wago_if.h soll nur von entweder io.c oder io_v2.c eingebunden werden"
#endif /* _WAGO_HW_IF_H_ */




