/**
 * M.c  2014-05-14
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
#include "M.h"

/** called by free(): put resources, forward to super. */
static void M_ops__destructor(struct M *M)
{
	TODO(Please add our **destructor** code here ...)
	_MY_TRACE_STR("M::_destructor()\n");
}
/** free memory after call destructor(). */
static void M_ops_free(struct M *M)
{
	TODO(Please add our **free** code here ...)
	/** PSEUDOCODE
	M__destructor(M);
	_MY_TRACE_STR("M::free()\n");
	free(M);
	*/
}

static void M_ops_put_here(struct M *M)
{
	_MY_TRACE_STR("M::put_here()\n");
}

static void M_ops_put_there(struct M *M)
{
	_MY_TRACE_STR("M::put_there()\n");
}
static struct M_ops M_ops = {
	._destructor = M_ops__destructor,
	.free = M_ops_free,
	.put_here = M_ops_put_here,
	.put_there = M_ops_put_there,
};

/** constructor(). */
void M_init(struct M *M)
{
	memset(M, sizeof(*M), 0);
	M->ops = &M_ops;
}