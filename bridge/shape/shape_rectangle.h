/**
 * shape_rectangle.h  2014-05-03 16:10:55
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
#ifndef __SHAPE_RECTANGLE_H__
#define __SHAPE_RECTANGLE_H__

#include <mycommon.h>

#include "shape.h"

struct shape_rectangle {
	struct shape shape;
};

void shape_rectangle_init(struct shape_rectangle *, struct color *);

#endif /* __SHAPE_RECTANGLE_H__ */
