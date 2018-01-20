/**
 * A.c  2014-05-14
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
#include "A.h"

/** called by free(): put resources, forward to super. */
static void A_ops__destructor(struct A *A)
{
	TODO(Please add our **destructor** code here ...)
	_MY_TRACE_STR("A::_destructor()\n");
}
/** free memory after call destructor(). */
static void A_ops_free(struct A *A)
{
	TODO(Please add our **free** code here ...)
	/** PSEUDOCODE
	A__destructor(A);
	_MY_TRACE_STR("A::free()\n");
	free(A);
	*/
}

static void A_ops_do_this(struct A *A)
{
	_MY_TRACE_STR("A::do_this()\n");
}

static void A_ops_do_that(struct A *A)
{
	_MY_TRACE_STR("A::do_that()\n");
}
static struct A_ops A_ops = {
	._destructor = A_ops__destructor,
	.free = A_ops_free,
	.do_this = A_ops_do_this,
	.do_that = A_ops_do_that,
};

/** constructor(). */
void A_init(struct A *A)
{
	memset(A, sizeof(*A), 0);
	A->ops = &A_ops;
}