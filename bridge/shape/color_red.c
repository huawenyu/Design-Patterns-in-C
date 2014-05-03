/**
 * color_red.c  2014-05-03 16:10:55
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
#include "color_red.h"

static void color_red_ops_render(struct color *color)
{
	/* struct color_red *a_color_red = container_of(color, typeof(*a_color_red), color);
	*/
	printf("color_red::render()\n");
}

static struct color_ops color_ops = {
	.render = color_red_ops_render,
};

void color_red_init(struct color_red *color_red)
{
	memset(color_red, sizeof(*color_red), 0);
	color_init(&color_red->color);
	CLASS_OPS_INIT(color_red->color.ops, color_ops);
}