/**
 * stack.c  2014-05-02 01:32:58
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

#include "stack.h"
#include "stack_impl_array.h"
#include "stack_impl_list.h"

/** called by free(): put resources, forward to super. */
static void stack_ops__destructor(struct stack *stack)
{
	printf("stack::_destructor()\n");
	/** pseudocode: careful about mult-inherit
	... do_something() to put resources ...
	CLASS_SUPER(stack, _destructor);
	*/
	if (stack->_impl)
		stack_impl_free(stack->_impl);
}
/** free memory after call destructor(). */
static void stack_ops_free(struct stack *stack)
{
	printf("stack::free()\n");
	/** pseudocode: careful about mult-inherit
	struct stack *l_stack = container_of(stack, typeof(*l_stack), );
	__destructor(stack);
	free(l_stack);
	*/
	stack__destructor(stack);
}

static void stack_ops_push(struct stack *stack, int val)
{
	printf("stack::push()\n");
	stack_impl_push(stack->_impl, val);
}

static int stack_ops_pop(struct stack *stack)
{
	printf("stack::pop()\n");
	return stack_impl_pop(stack->_impl);
}

static int stack_ops_top(struct stack *stack)
{
	printf("stack::top()\n");
	return stack_impl_top(stack->_impl);
}

static int stack_ops_is_empty(struct stack *stack)
{
	printf("stack::is_empty()\n");
	return stack_impl_is_empty(stack->_impl);
}

static int stack_ops_is_full(struct stack *stack)
{
	printf("stack::is_full()\n");
	return stack_impl_is_full(stack->_impl);
}

static struct stack_ops stack_ops = {
	._destructor = stack_ops__destructor,
	.free = stack_ops_free,
	.push = stack_ops_push,
	.pop = stack_ops_pop,
	.top = stack_ops_top,
	.is_empty = stack_ops_is_empty,
	.is_full = stack_ops_is_full,
};

void stack_init(struct stack *stack, const char *stack_impl)
{
	struct stack_impl_array *array;
	struct stack_impl_list *list;
	memset(stack, sizeof(*stack), 0);
	stack->ops = &stack_ops;

	stack->_impl = 0;
	if (0 == strcmp("array", stack_impl)) {
		array = malloc(sizeof(*array));
		stack_impl_array_init(array);
		stack->_impl = &array->stack_impl;
	}
	else if (0 == strcmp("list", stack_impl)) {
		list = malloc(sizeof(*list));
		stack_impl_list_init(list);
		stack->_impl = &list->stack_impl;
	}
}

