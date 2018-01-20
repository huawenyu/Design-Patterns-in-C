/**
 * component.c  2014-05-04
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
#include "component.h"

static void component_ops_traverse(struct component *component)
{
	_MY_TRACE_STR("component::traverse()\n");
}
static struct component_ops component_ops = {
	.traverse = component_ops_traverse,
};

void component_init(struct component *component)
{
	memset(component, sizeof(*component), 0);
	component->ops = &component_ops;
}