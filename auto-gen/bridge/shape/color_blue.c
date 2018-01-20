/**
 * color_blue.c  2014-05-03 16:10:55
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
#include "color_blue.h"

static void color_blue_ops_render(struct color *color)
{
	/* struct color_blue *a_color_blue = container_of(color, typeof(*a_color_blue), color);
	*/
	_MY_TRACE_STR("color_blue::render()\n");
}

static struct color_ops color_ops = {
	.render = color_blue_ops_render,
};

void color_blue_init(struct color_blue *color_blue)
{
	_MY_TRACE_STR("color_blue_init()\n");
	memset(color_blue, sizeof(*color_blue), 0);
	color_init(&color_blue->color);
	CLASS_OPS_INIT(color_blue->color.ops, color_ops);
}
