/**
 * decorator.c  2014-05-08
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
#include "decorator.h"

static struct decorator_ops decorator_ops = {0
};

static void decorator_ops_write(struct interface *interface, char *buf)
{
	/* struct decorator *a_decorator = container_of(interface, typeof(*a_decorator), interface);
	*/
	_MY_TRACE_STR("decorator::write()\n");
}

static void decorator_ops_read(struct interface *interface, char *buf)
{
	/* struct decorator *a_decorator = container_of(interface, typeof(*a_decorator), interface);
	*/
	_MY_TRACE_STR("decorator::read()\n");
}

static struct interface_ops interface_ops = {
	.write = decorator_ops_write,
	.read = decorator_ops_read,
};

/** constructor(). */
void decorator_init(struct decorator *decorator, struct interface *inner)
{
	memset(decorator, sizeof(*decorator), 0);
	interface_init(&decorator->interface);
	CLASS_OPS_INIT_SUPER(decorator->interface.ops, interface_ops);
	decorator->ops = &decorator_ops;
	decorator->_inner = inner;
}