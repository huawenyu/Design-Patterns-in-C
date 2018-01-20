/**
 * shape_rectangle.c  2014-05-03 16:10:55
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
#include <mytrace.h>
#include "shape_rectangle.h"

/** called by free(): put resources, forward to super. */
static void shape_rectangle_ops__destructor(struct shape *shape)
{
	_MY_TRACE_STR("shape_rectangle::_destructor()\n");
	CLASS_SUPER(shape, _destructor);
}
/** free memory after call destructor(). */
static void shape_rectangle_ops_free(struct shape *shape)
{
	struct shape_rectangle *a_shape_rectangle = container_of(shape, typeof(*a_shape_rectangle), shape);
	shape__destructor(shape);
	_MY_TRACE_STR("shape_rectangle::free()\n");
	free(a_shape_rectangle);
}

static void shape_rectangle_ops_draw(struct shape *shape)
{
	/* struct shape_rectangle *a_shape_rectangle = container_of(shape, typeof(*a_shape_rectangle), shape);
	*/
	_MY_TRACE_STR("shape_rectangle::draw()\n");
	CLASS_SUPER(shape, draw);
}

static struct shape_ops shape_ops = {
	._destructor = shape_rectangle_ops__destructor,
	.free = shape_rectangle_ops_free,
	.draw = shape_rectangle_ops_draw,
};

void shape_rectangle_init(struct shape_rectangle *shape_rectangle, struct color *color)
{
	_MY_TRACE_STR("shape_rectangle_init()\n");
	memset(shape_rectangle, sizeof(*shape_rectangle), 0);
	shape_init(&shape_rectangle->shape, color);
	CLASS_OPS_INIT_SUPER(shape_rectangle->shape.ops, shape_ops);
}
