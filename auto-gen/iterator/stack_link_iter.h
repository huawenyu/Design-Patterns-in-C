/**
 * stack_link_iter.h  2014-05-16
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
#ifndef __STACK_LINK_ITER_H__
#define __STACK_LINK_ITER_H__

#include <mycommon.h>
#include <mytrace.h>

#include "iterator.h"
#include "stack_link.h"

/** Take traversal-of-a-collection functionality out of the collection and
    promote it to "full object status". */
struct stack_link_iter {
	struct iterator iterator;
	struct stack_link * _stack_link;
	struct data_node * _current; /** As cursor of stack_link */
};

/** constructor(). */
void stack_link_iter_init(struct stack_link_iter *stack_link_iter, struct stack_link *stack_link);

#endif /* __STACK_LINK_ITER_H__ */
