/**
 * color.h  2014-05-03 16:10:55
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
#ifndef __COLOR_H__
#define __COLOR_H__

#include <mycommon.h>

struct color_ops;

struct color {
	struct color_ops *ops;
};
struct color_ops {
	void (*render)(struct color *);
};
void color_init(struct color *);

static inline void color_render(struct color *color)
{
	color->ops->render(color);
}

#endif /* __COLOR_H__ */