/**
 * me.c  2014-05-14
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "me.h"

static struct A_ops A_ops = {0
};

static struct A_ops A_ops_2 = {0
};

static struct A_ops A_ops_3 = {0
};

static struct M_ops M_ops_4 = {0
};

static struct P_ops P_ops_5 = {0
};

/** constructor(). */
void me_init(struct me *me)
{
	memset(me, sizeof(*me), 0);
	A_B1_init(&me->A_B1);
	CLASS_OPS_INIT_SUPER(me->A_B1.A.ops, A_ops);
	A_B2_init(&me->A_B2);
	CLASS_OPS_INIT_SUPER(me->A_B2.A.ops, A_ops_2);
	A_B3_init(&me->A_B3);
	CLASS_OPS_INIT_SUPER(me->A_B3.A.ops, A_ops_3);
	M_N_init(&me->M_N);
	CLASS_OPS_INIT_SUPER(me->M_N.M.ops, M_ops_4);
	P_Q_init(&me->P_Q);
	CLASS_OPS_INIT_SUPER(me->P_Q.P.ops, P_ops_5);
}