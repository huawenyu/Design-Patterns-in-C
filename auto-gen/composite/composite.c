/**
 * composite.c  2014-05-04
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
#include "composite.h"

static void composite_ops_traverse(struct component *component)
{
	int ii;
	struct composite *a_composite = container_of(component, typeof(*a_composite), component);
	//_MY_TRACE_STR("composite::traverse()\n");
	printf("%d  \n", a_composite->value);
	for (ii=0; ii < a_composite->children_sz; ++ii) {
		component_traverse(a_composite->children[ii]);
	}
}

static struct component_ops component_ops = {
	.traverse = composite_ops_traverse,
};

void composite_init(struct composite *composite, int val)
{
	memset(composite, sizeof(*composite), 0);
	component_init(&composite->component);
	CLASS_OPS_INIT_SUPER(composite->component.ops, component_ops);
	composite->value = val;
}

void composite_add(struct composite *composite, struct component *c)
{
	//_MY_TRACE_STR("composite::add()\n");
	composite->children[composite->children_sz++] = c;
}
