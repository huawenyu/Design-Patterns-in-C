/**
 * grandgirl.c  2014-05-02 23:11:33
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
#include <myobj.h>
#include "grandgirl.h"

/** called by free(): put resources, forward to super. */
static void grandgirl_ops__destructor(struct parent *parent)
{
	printf("grandgirl::_destructor()\n");
	/** PSEUDOCODE
	... do_something() to put resources ...
	CLASS_SUPER(parent, _destructor);
	*/
}
/** free memory after call destructor(). */
static void grandgirl_ops_free(struct parent *parent)
{
	printf("grandgirl::free()\n");
	/** PSEUDOCODE
	struct grandgirl *l_grandgirl = container_of(parent, typeof(*l_grandgirl), parent);
	parent__destructor(parent);
	free(l_grandgirl);
	*/
}

static void grandgirl_ops_pub_v_func1(struct parent *parent)
{
	printf("grandgirl::pub_v_func1()\n");
}

static void grandgirl_ops_pub_v_func2(struct parent *parent)
{
	printf("grandgirl::pub_v_func2()\n");
}

static void grandgirl_ops_pri_v_func3(struct parent *parent)
{
	printf("grandgirl::pri_v_func3()\n");
}

static void grandgirl_ops_pri_v_func4(struct parent *parent)
{
	printf("grandgirl::pri_v_func4()\n");
}

static struct parent_ops parent_ops = {
	._destructor = grandgirl_ops__destructor,
	.free = grandgirl_ops_free,
	.pub_v_func1 = grandgirl_ops_pub_v_func1,
	.pub_v_func2 = grandgirl_ops_pub_v_func2,
	.pri_v_func3 = grandgirl_ops_pri_v_func3,
	.pri_v_func4 = grandgirl_ops_pri_v_func4,
};

void grandgirl_init(struct grandgirl *grandgirl)
{
	memset(grandgirl, sizeof(*grandgirl), 0);
	child_init(&grandgirl->child);
	CLASS_OPS_INIT_SUPER(grandgirl->child.parent.ops, parent_ops);
}