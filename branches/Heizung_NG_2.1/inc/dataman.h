#ifndef _DATAMAN_H_
#define _DATAMAN_H_

#include "gen_types.h"

#include "reg.h"
#include "zeit.h"
#include "task.h"
#include "sol.h"
#include "fb.h"
#include "hk.h"
#include "ww.h"
#include "kes.h"
#include "err.h"

typedef struct dataman_in_s {
    sol_in_t    sol;
    fb_in_t     fb;
    hk_in_t     hk;
    ww_in_t     ww;

};


#endif /* _DATAMAN_H_ */
