/**
 * wrapper.c  2014-05-08
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
#include "wrapper.h"

/** called by free(): put resources, forward to super. */
static void wrapper_ops__destructor(struct decorator *decorator)
{
	TODO(Please add our **destructor** code here ...)
	/** PSEUDOCODE
	... do_something() to put resources ...
	_MY_TRACE_STR("wrapper::_destructor()\n");
	CLASS_SUPER(decorator, _destructor);
	*/
}
/** free memory after call destructor(). */
static void wrapper_ops_free(struct decorator *decorator)
{
	TODO(Please add our **free** code here ...)
	/** PSEUDOCODE
	struct wrapper *a_wrapper = container_of(decorator, typeof(*a_wrapper), decorator);
	decorator__destructor(decorator);
	_MY_TRACE_STR("wrapper::free()\n");
	free(a_wrapper);
	*/
}

static struct decorator_ops decorator_ops = {
	._destructor = wrapper_ops__destructor,
	.free = wrapper_ops_free,
};

static void wrapper_ops_write(struct interface *interface, char *buf)
{
	/* struct wrapper *a_wrapper = container_of(interface, typeof(*a_wrapper), decorator.interface);
	*/
	_MY_TRACE_STR("wrapper::write()\n");
}

static void wrapper_ops_read(struct interface *interface, char *buf)
{
	/* struct wrapper *a_wrapper = container_of(interface, typeof(*a_wrapper), decorator.interface);
	*/
	_MY_TRACE_STR("wrapper::read()\n");
}

static struct interface_ops interface_ops = {
	.write = wrapper_ops_write,
	.read = wrapper_ops_read,
};

/** constructor(). */
void wrapper_init(struct wrapper *wrapper, struct interface *inner, char *str)
{
	memset(wrapper, sizeof(*wrapper), 0);
	decorator_init(&wrapper->decorator, inner);
	CLASS_OPS_INIT_SUPER(wrapper->decorator.ops, decorator_ops);
	CLASS_OPS_INIT(wrapper->decorator.interface.ops, interface_ops);
}