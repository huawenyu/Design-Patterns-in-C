/**
 * primitive.c  2014-05-04
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
#include "primitive.h"

static void primitive_ops_traverse(struct component *component)
{
	struct primitive *a_primitive = container_of(component, typeof(*a_primitive), component);
	//_MY_TRACE_STR("primitive::traverse()\n");
	printf("%d  \n", a_primitive->value);
}

static struct component_ops component_ops = {
	.traverse = primitive_ops_traverse,
};

void primitive_init(struct primitive *primitive, int val)
{
	memset(primitive, sizeof(*primitive), 0);
	component_init(&primitive->component);
	CLASS_OPS_INIT_SUPER(primitive->component.ops, component_ops);
	primitive->value = val;
}
