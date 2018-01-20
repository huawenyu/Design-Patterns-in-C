/**
 * parent.c  2014-05-03 15:06:28
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
#include "parent.h"

static void parent_pri_m_func3(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pri_m_func3()\n");
}

static void parent_static_pri_m_func4(void)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::static_pri_m_func4()\n");
}
/** called by free(): put resources, forward to super. */
static void parent_ops__destructor(struct parent *parent)
{
	printf("parent::_destructor()\n");
}
/** free memory after call destructor(). */
static void parent_ops_free(struct parent *parent)
{
	parent__destructor(parent);
	printf("parent::free()\n");
	free(parent);
}

static void parent_ops_pub_v_func1(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pub_v_func1()\n");
}

static void parent_ops_pub_v_func2(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pub_v_func2()\n");
}

static void parent_ops_pri_v_func3(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pri_v_func3()\n");
}

static void parent_ops_pri_v_func4(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pri_v_func4()\n");
}
static struct parent_ops parent_ops = {
	._destructor = parent_ops__destructor,
	.free = parent_ops_free,
	.pub_v_func1 = parent_ops_pub_v_func1,
	.pub_v_func2 = parent_ops_pub_v_func2,
	.pri_v_func3 = parent_ops_pri_v_func3,
	.pri_v_func4 = parent_ops_pri_v_func4,
};

void parent_init(struct parent *parent)
{
	memset(parent, sizeof(*parent), 0);
	parent->ops = &parent_ops;
}

void parent_pub_m_func1(struct parent *parent)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::pub_m_func1()\n");
	parent_pri_m_func3(parent);
}

void parent_static_pub_m_func2(void)
{
	/*struct parent *a_parent = container_of(parent, typeof(*a_parent), );
	*/
	printf("parent::static_pub_m_func2()\n");
	parent_static_pri_m_func4();
}
