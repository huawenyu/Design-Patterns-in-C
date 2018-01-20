/**
 * row.c  2014-05-04
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
#include "row.h"

static void row_ops_traverse(struct component *component)
{
	/* struct row *a_row = container_of(component, typeof(*a_row), composite.component);
	*/
	//_MY_TRACE_STR("row::traverse()\n");
	printf("row  ");
	CLASS_SUPER(component, traverse);
}

static struct component_ops component_ops = {
	.traverse = row_ops_traverse,
};

void row_init(struct row *row, int val)
{
	memset(row, sizeof(*row), 0);
	composite_init(&row->composite, val);
	CLASS_OPS_INIT_SUPER(row->composite.component.ops, component_ops);
}
