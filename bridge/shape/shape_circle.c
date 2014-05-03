/**
 * shape_circle.c  2014-05-03 16:10:55
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
#include "shape_circle.h"

/** called by free(): put resources, forward to super. */
static void shape_circle_ops__destructor(struct shape *shape)
{
	printf("shape_circle::_destructor()\n");
	CLASS_SUPER(shape, _destructor);
}
/** free memory after call destructor(). */
static void shape_circle_ops_free(struct shape *shape)
{
	struct shape_circle *a_shape_circle = container_of(shape, typeof(*a_shape_circle), shape);
	shape__destructor(shape);
	printf("shape_circle::free()\n");
	free(a_shape_circle);
}

static void shape_circle_ops_draw(struct shape *shape)
{
	/* struct shape_circle *a_shape_circle = container_of(shape, typeof(*a_shape_circle), shape);
	*/
	printf("shape_circle::draw()\n");
}

static struct shape_ops shape_ops = {
	._destructor = shape_circle_ops__destructor,
	.free = shape_circle_ops_free,
	.draw = shape_circle_ops_draw,
};

void shape_circle_init(struct shape_circle *shape_circle, struct color *color)
{
	memset(shape_circle, sizeof(*shape_circle), 0);
	shape_init(&shape_circle->shape, color);
	CLASS_OPS_INIT_SUPER(shape_circle->shape.ops, shape_ops);
}
