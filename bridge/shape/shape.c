/**
 * shape.c  2014-05-03 16:10:55
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
#include "shape.h"

/** called by free(): put resources, forward to super. */
static void shape_ops__destructor(struct shape *shape)
{
	_MY_TRACE_STR("shape::_destructor()\n");
}
/** free memory after call destructor(). */
static void shape_ops_free(struct shape *shape)
{
	shape__destructor(shape);
	_MY_TRACE_STR("shape::free()\n");
	free(shape);
}

static void shape_ops_draw(struct shape *shape)
{
	_MY_TRACE_STR("shape::draw()\n");
	color_render(shape->_color);
}
static struct shape_ops shape_ops = {
	._destructor = shape_ops__destructor,
	.free = shape_ops_free,
	.draw = shape_ops_draw,
};

void shape_init(struct shape *shape, struct color *color)
{
	memset(shape, sizeof(*shape), 0);
	shape->ops = &shape_ops;
	shape->_color = color;
}
