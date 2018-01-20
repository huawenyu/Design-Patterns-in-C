/**
 * stack_link_iter.c  2014-05-16
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "stack_link_iter.h"

static void stack_link_iter_ops_first(struct iterator *iterator)
{
	struct stack_link_iter *a_stack_link_iter = container_of(iterator, typeof(*a_stack_link_iter), iterator);
	
	_MY_TRACE_STR("stack_link_iter::first()\n");
	a_stack_link_iter->_current = 0;
	if (!stack_is_empty(&a_stack_link_iter->_stack_link->stack)) {
		a_stack_link_iter->_current = a_stack_link_iter->_stack_link->link.next;
	}
}

static void stack_link_iter_ops_next(struct iterator *iterator)
{
	/* struct stack_link_iter *a_stack_link_iter = container_of(iterator, typeof(*a_stack_link_iter), iterator);
	*/
	_MY_TRACE_STR("stack_link_iter::next()\n");
}
/** return bool */
static int stack_link_iter_ops_is_end(struct iterator *iterator)
{
	/* struct stack_link_iter *a_stack_link_iter = container_of(iterator, typeof(*a_stack_link_iter), iterator);
	*/
	_MY_TRACE_STR("stack_link_iter::is_end()\n");
	return 0;
}

static struct data_node * stack_link_iter_ops_current(struct iterator *iterator)
{
	/* struct stack_link_iter *a_stack_link_iter = container_of(iterator, typeof(*a_stack_link_iter), iterator);
	*/
	_MY_TRACE_STR("stack_link_iter::current()\n");
	return 0;
}

static struct iterator_ops iterator_ops = {
	.first = stack_link_iter_ops_first,
	.next = stack_link_iter_ops_next,
	.is_end = stack_link_iter_ops_is_end,
	.current = stack_link_iter_ops_current,
};

/** constructor(). */
void stack_link_iter_init(struct stack_link_iter *stack_link_iter, struct stack_link *stack_link)
{
	_MY_TRACE_STR("stack_link_iter_init()\n");
	memset(stack_link_iter, sizeof(*stack_link_iter), 0);
	iterator_init(&stack_link_iter->iterator);
	CLASS_OPS_INIT(stack_link_iter->iterator.ops, iterator_ops);
	stack_link_iter->_stack_link = stack_link;
}
