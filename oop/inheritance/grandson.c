/**
 * grandson.c  2014-05-02 23:11:33
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
#include "grandson.h"

/** called by free(): put resources, forward to super. */
static void grandson_ops__destructor(struct parent *parent)
{
	printf("grandson::_destructor()\n");
	/** PSEUDOCODE
	... do_something() to put resources ...
	CLASS_SUPER(parent, _destructor);
	*/
}
/** free memory after call destructor(). */
static void grandson_ops_free(struct parent *parent)
{
	printf("grandson::free()\n");
	/** PSEUDOCODE
	struct grandson *l_grandson = container_of(parent, typeof(*l_grandson), parent);
	parent__destructor(parent);
	free(l_grandson);
	*/
}

static void grandson_ops_pub_v_func1(struct parent *parent)
{
	printf("grandson::pub_v_func1()\n");
}

static void grandson_ops_pub_v_func2(struct parent *parent)
{
	printf("grandson::pub_v_func2()\n");
}

static void grandson_ops_pri_v_func3(struct parent *parent)
{
	printf("grandson::pri_v_func3()\n");
}

static void grandson_ops_pri_v_func4(struct parent *parent)
{
	printf("grandson::pri_v_func4()\n");
}

static struct parent_ops parent_ops = {
	._destructor = grandson_ops__destructor,
	.free = grandson_ops_free,
	.pub_v_func1 = grandson_ops_pub_v_func1,
	.pub_v_func2 = grandson_ops_pub_v_func2,
	.pri_v_func3 = grandson_ops_pri_v_func3,
	.pri_v_func4 = grandson_ops_pri_v_func4,
};

void grandson_init(struct grandson *grandson)
{
	memset(grandson, sizeof(*grandson), 0);
	child_init(&grandson->child);
	CLASS_OPS_INIT_SUPER(grandson->child.parent.ops, parent_ops);
}