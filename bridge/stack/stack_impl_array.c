/**
 * stack_impl_array.c  2014-05-02 01:32:58
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
#include <myobj.h>
#include "stack_impl_array.h"

/** called by free(): put resources, forward to super. */
static void stack_impl_array_ops__destructor(struct stack_impl *stack_impl)
{
	printf("stack_impl_array::_destructor()\n");
	/** pseudocode: careful about mult-inherit
	... do_something() to put resources ...
	CLASS_SUPER(stack_impl_array, _destructor);
	*/
}
/** free memory after call destructor(). */
static void stack_impl_array_ops_free(struct stack_impl *stack_impl)
{
	printf("stack_impl_array::free()\n");
	/** pseudocode: careful about mult-inherit
	struct stack_impl_array *l_stack_impl_array = container_of(stack_impl_array, typeof(*l_stack_impl_array), stack_impl);
	stack_impl__destructor(stack_impl_array);
	free(l_stack_impl_array);
	*/
}

static void stack_impl_array_ops_push(struct stack_impl *stack_impl, int val)
{
	struct stack_array *array = container_of(stack_impl, typeof(*array), stack_impl);
	printf("stack_impl_array::push()\n");
	if (!stack_impl_is_full(stack_impl))
		array->items[array->total++] = val;
}

static int stack_impl_array_ops_pop(struct stack_impl *stack_impl)
{
	struct stack_array *array = container_of(stack_impl, typeof(*array), stack_impl);
	printf("stack_impl_array::pop()\n");
	if (stack_impl_is_empty(stack_impl))
		return -1;
	return array->items[--array->total];
}

static int stack_impl_array_ops_top(struct stack_impl *stack_impl)
{
	struct stack_array *array = container_of(stack_impl, typeof(*array), stack_impl);
	printf("stack_impl_array::top()\n");
	if (stack_impl_is_empty(stack_impl))
		return -1;
	return array->items[array->total-1];
}

static int stack_impl_array_ops_is_empty(struct stack_impl *stack_impl)
{
	struct stack_array *array = container_of(stack_impl, typeof(*array), stack_impl);
	printf("stack_impl_array::is_empty()\n");
	return (array->total == 0);
}

static int stack_impl_array_ops_is_full(struct stack_impl *stack_impl)
{
	struct stack_array *array = container_of(stack_impl, typeof(*array), stack_impl);
	printf("stack_impl_array::is_full()\n");
	return (array->total == stack_array_items_size);
}

static void stack_impl_array_ops_free(struct stack_impl *stack_impl)
{
	printf("stack_impl_array::free()\n");
	/** pseudocode: careful about mult-inherit
	struct stack_impl_array *l_stack_impl_array = container_of(stack_impl_array, typeof(*l_stack_impl_array), stack_impl);
	stack_impl__destructor(stack_impl_array);
	free(l_stack_impl_array);
	*/
}

static struct stack_impl_ops stack_impl_ops = {
	._destructor = stack_impl_array_ops__destructor,
	.free = stack_impl_array_ops_free,
	.push = stack_impl_array_ops_push,
	.pop = stack_impl_array_ops_pop,
	.top = stack_impl_array_ops_top,
	.is_empty = stack_impl_array_ops_is_empty,
	.is_full = stack_impl_array_ops_is_full,
	.free = stack_impl_array_ops_free,
};

void stack_impl_array_init(struct stack_impl_array *stack_impl_array)
{
	memset(stack_impl_array, sizeof(*stack_impl_array), 0);
	stack_impl_init(&stack_impl_array->stack_impl);
	CLASS_OPS_INIT(stack_impl_array->stack_impl.ops, stack_impl_ops);
}