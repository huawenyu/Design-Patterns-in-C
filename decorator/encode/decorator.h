/**
 * decorator.h  2014-05-08
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
#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include <mycommon.h>
#include <mytrace.h>

#include "interface.h"

struct decorator_ops;

struct decorator {
	struct interface interface;
	struct decorator_ops *ops;
	struct interface * _inner;
};
struct decorator_ops {
	void (*_destructor)(struct decorator *); /** called by free(): put resources, forward to super. */
	void (*free)(struct decorator *); /** free memory after call destructor(). */
	struct decorator_ops *__super;
};

/** constructor(). */
void decorator_init(struct decorator *decorator, struct interface *inner);

/** called by free(): put resources, forward to super. */
static inline void decorator__destructor(struct decorator *decorator)
{
	decorator->ops->_destructor(decorator);
}
/** free memory after call destructor(). */
static inline void decorator_free(struct decorator *decorator)
{
	decorator->ops->free(decorator);
}

#endif /* __DECORATOR_H__ */