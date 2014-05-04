/**
 * component.h  2014-05-04
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
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <mycommon.h>
#include <mytrace.h>

struct component_ops;

struct component {
	struct component_ops *ops;
};
struct component_ops {
	void (*traverse)(struct component *);
	struct component_ops *__super;
};
void component_init(struct component *);

static inline void component_traverse(struct component *component)
{
	component->ops->traverse(component);
}

#endif /* __COMPONENT_H__ */