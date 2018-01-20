/**
 * column.c  2014-05-04
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
#include "column.h"

static void column_ops_traverse(struct component *component)
{
	/* struct column *a_column = container_of(component, typeof(*a_column), composite.component);
	*/
	//_MY_TRACE_STR("column::traverse()\n");
	printf("column  ");
	CLASS_SUPER(component, traverse);
}

static struct component_ops component_ops = {
	.traverse = column_ops_traverse,
};

void column_init(struct column *column, int val)
{
	memset(column, sizeof(*column), 0);
	composite_init(&column->composite, val);
	CLASS_OPS_INIT_SUPER(column->composite.component.ops, component_ops);
}
