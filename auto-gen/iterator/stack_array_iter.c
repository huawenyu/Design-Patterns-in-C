/**
 * stack_array_iter.c  2014-05-16
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
#include "stack_array_iter.h"

static void stack_array_iter_ops_first(struct iterator *iterator)
{
	struct stack_array_iter *a_stack_array_iter = container_of(iterator, typeof(*a_stack_array_iter), iterator);
	
	_MY_TRACE_STR("stack_array_iter::first()\n");
	a_stack_array_iter->_pos = -1;
	if (!stack_is_empty(&a_stack_array_iter->_stack_array->stack)) {
		a_stack_array_iter->_pos = 0;
	}
}

static void stack_array_iter_ops_next(struct iterator *iterator)
{
	struct stack_array_iter *a_stack_array_iter = container_of(iterator, typeof(*a_stack_array_iter), iterator);
	
	_MY_TRACE_STR("stack_array_iter::next()\n");
	a_stack_array_iter->_pos++;
}
/** return bool */
static int stack_array_iter_ops_is_end(struct iterator *iterator)
{
	struct stack_array_iter *a_stack_array_iter = container_of(iterator, typeof(*a_stack_array_iter), iterator);
	
	_MY_TRACE_STR("stack_array_iter::is_end()\n");
	return a_stack_array_iter->_pos >= a_stack_array_iter->_stack_array->top;
}

static struct data_node * stack_array_iter_ops_current(struct iterator *iterator)
{
	struct stack_array_iter *a_stack_array_iter = container_of(iterator, typeof(*a_stack_array_iter), iterator);
	
	_MY_TRACE_STR("stack_array_iter::current()\n");
	if (a_stack_array_iter->_pos >= 0
		&& a_stack_array_iter->_pos < a_stack_array_iter->_stack_array->top)
		return  a_stack_array_iter->_stack_array->arr[a_stack_array_iter->_pos];
	return 0;
}

static struct iterator_ops iterator_ops = {
	.first = stack_array_iter_ops_first,
	.next = stack_array_iter_ops_next,
	.is_end = stack_array_iter_ops_is_end,
	.current = stack_array_iter_ops_current,
};

/** constructor(). */
void stack_array_iter_init(struct stack_array_iter *stack_array_iter, struct stack_array *stack_array)
{
	_MY_TRACE_STR("stack_array_iter_init()\n");
	memset(stack_array_iter, sizeof(*stack_array_iter), 0);
	iterator_init(&stack_array_iter->iterator);
	CLASS_OPS_INIT(stack_array_iter->iterator.ops, iterator_ops);
	stack_array_iter->_stack_array = stack_array;
	stack_array_iter->_pos = -1;
}
