/**
 * M_N.c  2014-05-14
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
#include "M_N.h"

static struct M_ops M_ops = {0
};

/** constructor(). */
void M_N_init(struct M_N *M_N)
{
	memset(M_N, sizeof(*M_N), 0);
	M_init(&M_N->M);
	CLASS_OPS_INIT_SUPER(M_N->M.ops, M_ops);
}