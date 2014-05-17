/**
 * stack_array.c  2014-05-16
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
#include "stack_array.h"
#include "stack_array_iter.h"

static void stack_array_ops_push(struct stack *stack, struct data_node *node)
{
	struct stack_array *a_stack_array = container_of(stack, typeof(*a_stack_array), stack);
	
	_MY_TRACE_STR("stack_array::push()\n");
	if (!stack_is_full(stack))
		a_stack_array->arr[a_stack_array->top++] = node;
}

static struct data_node * stack_array_ops_pop(struct stack *stack)
{
	struct stack_array *a_stack_array = container_of(stack, typeof(*a_stack_array), stack);
	
	_MY_TRACE_STR("stack_array::pop()\n");
	if (!stack_is_empty(stack))
		return a_stack_array->arr[--a_stack_array->top];
	return 0;
}
/** return bool */
static int stack_array_ops_is_empty(struct stack *stack)
{
	struct stack_array *a_stack_array = container_of(stack, typeof(*a_stack_array), stack);
	
	_MY_TRACE_STR("stack_array::is_empty()\n");
	return a_stack_array->top <= 0;
}
/** return bool */
static int stack_array_ops_is_full(struct stack *stack)
{
	struct stack_array *a_stack_array = container_of(stack, typeof(*a_stack_array), stack);
	
	_MY_TRACE_STR("stack_array::is_full()\n");
	return a_stack_array->top >= STACK_ARRAY_MAX;
}

static struct iterator * stack_array_ops_create_iter(struct stack *stack)
{
	struct stack_array_iter *iter;
	struct stack_array *a_stack_array = container_of(stack, typeof(*a_stack_array), stack);

	_MY_TRACE_STR("stack_array::create_iter()\n");
	iter = malloc(sizeof(*iter));
	stack_array_iter_init(iter, a_stack_array);
	return &iter->iterator;
}

static struct stack_ops stack_ops = {
	.push = stack_array_ops_push,
	.pop = stack_array_ops_pop,
	.is_empty = stack_array_ops_is_empty,
	.is_full = stack_array_ops_is_full,
	.create_iter = stack_array_ops_create_iter,
};

/** constructor(). */
void stack_array_init(struct stack_array *stack_array)
{
	_MY_TRACE_STR("stack_array_init()\n");
	memset(stack_array, sizeof(*stack_array), 0);
	stack_init(&stack_array->stack);
	CLASS_OPS_INIT_SUPER(stack_array->stack.ops, stack_ops);
}
