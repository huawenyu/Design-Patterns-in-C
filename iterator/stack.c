/**
 * stack.c  2014-05-16
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
#include "stack.h"

static void stack_ops_push(struct stack *stack, struct data_node *node)
{
	_MY_TRACE_STR("stack::push()\n");
}

static struct data_node * stack_ops_pop(struct stack *stack)
{
	_MY_TRACE_STR("stack::pop()\n");
	return 0;
}
/** return bool */
static int stack_ops_is_empty(struct stack *stack)
{
	_MY_TRACE_STR("stack::is_empty()\n");
	return 0;
}
/** return bool */
static int stack_ops_is_full(struct stack *stack)
{
	_MY_TRACE_STR("stack::is_full()\n");
	return 0;
}

static struct iterator * stack_ops_create_iter(struct stack *stack)
{
	_MY_TRACE_STR("stack::create_iter()\n");
	return 0;
}
static struct stack_ops stack_ops = {
	.push = stack_ops_push,
	.pop = stack_ops_pop,
	.is_empty = stack_ops_is_empty,
	.is_full = stack_ops_is_full,
	.create_iter = stack_ops_create_iter,
};

/** constructor(). */
void stack_init(struct stack *stack)
{
	_MY_TRACE_STR("stack_init()\n");
	memset(stack, sizeof(*stack), 0);
	stack->ops = &stack_ops;
}