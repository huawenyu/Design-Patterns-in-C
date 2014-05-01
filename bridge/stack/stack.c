
/**
 * stack.c  2014-04-30 16:29:05
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
#include "stack_array.h"
#include "stack_list.h"


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
	.push = stack_ops_push,
	.pop = stack_ops_pop,
	.top = stack_ops_top,
	.is_empty = stack_ops_is_empty,
	.is_full = stack_ops_is_full,
};

void stack_init(struct stack *stack, char *stack_impl)
{
	struct stack_array *array;
	struct stack_list *list;
	memset(stack, sizeof(*stack), 0);
	stack->ops = &stack_ops;

	_impl = 0;
	if (0 == strcmp("array", stack_impl)) {
		array = malloc(sizeof(*array));
		stack_array_init(array);
		_impl = &array->stack_impl;
	}
	else if (0 == strcmp("list", stack_impl)) {
		list = malloc(sizeof(*list));
		stack_array_init(list);
		_impl = &list->stack_impl;
	}
}

