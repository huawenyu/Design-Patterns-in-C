/**
 * P.c  2014-05-14
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
#include "P.h"

/** called by free(): put resources, forward to super. */
static void P_ops__destructor(struct P *P)
{
	TODO(Please add our **destructor** code here ...)
	_MY_TRACE_STR("P::_destructor()\n");
}
/** free memory after call destructor(). */
static void P_ops_free(struct P *P)
{
	TODO(Please add our **free** code here ...)
	/** PSEUDOCODE
	P__destructor(P);
	_MY_TRACE_STR("P::free()\n");
	free(P);
	*/
}
static struct P_ops P_ops = {
	._destructor = P_ops__destructor,
	.free = P_ops_free,
};

/** constructor(). */
void P_init(struct P *P)
{
	memset(P, sizeof(*P), 0);
	P->ops = &P_ops;
}