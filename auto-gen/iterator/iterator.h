/**
 * iterator.h  2014-05-16
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C *
 * 
 * Add iterator to the container:
    - Design an "iterator" class for the "container" class
    - Add a createIterator() member to the container class
    - Clients ask the container object to create an iterator object
    - Clients use the first(), isDone(), next(), and currentItem() protocol
 */
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <mycommon.h>
#include <mytrace.h>

#include "data_node.h"

struct iterator_ops;
/** Take traversal-of-a-collection functionality out of the collection and
    promote it to "full object status". */
struct iterator {
	struct iterator_ops *ops;
};
struct iterator_ops {
	void (*first)(struct iterator *);
	void (*next)(struct iterator *);
	int (*is_end)(struct iterator *); /** return bool */
	struct data_node * (*current)(struct iterator *);
};

/** constructor(). */
void iterator_init(struct iterator *iterator);

static inline void iterator_first(struct iterator *iterator)
{
	iterator->ops->first(iterator);
}

static inline void iterator_next(struct iterator *iterator)
{
	iterator->ops->next(iterator);
}
/** return bool */
static inline int iterator_is_end(struct iterator *iterator)
{
	return iterator->ops->is_end(iterator);
}

static inline struct data_node * iterator_current(struct iterator *iterator)
{
	return iterator->ops->current(iterator);
}

#endif /* __ITERATOR_H__ */