/**
 * stack_link.c  2014-05-16
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
#include "stack_link.h"
#include "stack_link_iter.h"

static void stack_link_ops_push(struct stack *stack, struct data_node *node)
{
	/* struct stack_link *a_stack_link = container_of(stack, typeof(*a_stack_link), stack);
	*/
	_MY_TRACE_STR("stack_link::push()\n");
}

static struct data_node * stack_link_ops_pop(struct stack *stack)
{
	/* struct stack_link *a_stack_link = container_of(stack, typeof(*a_stack_link), stack);
	*/
	_MY_TRACE_STR("stack_link::pop()\n");
	return 0;
}
/** return bool */
static int stack_link_ops_is_empty(struct stack *stack)
{
	/* struct stack_link *a_stack_link = container_of(stack, typeof(*a_stack_link), stack);
	*/
	_MY_TRACE_STR("stack_link::is_empty()\n");
	return 0;
}
/** return bool */
static int stack_link_ops_is_full(struct stack *stack)
{
	/* struct stack_link *a_stack_link = container_of(stack, typeof(*a_stack_link), stack);
	*/
	_MY_TRACE_STR("stack_link::is_full()\n");
	return 0;
}

static struct iterator * stack_link_ops_create_iter(struct stack *stack)
{
	/* struct stack_link *a_stack_link = container_of(stack, typeof(*a_stack_link), stack);
	*/
	_MY_TRACE_STR("stack_link::create_iter()\n");
	return 0;
}

static struct stack_ops stack_ops = {
	.push = stack_link_ops_push,
	.pop = stack_link_ops_pop,
	.is_empty = stack_link_ops_is_empty,
	.is_full = stack_link_ops_is_full,
	.create_iter = stack_link_ops_create_iter,
};

/** constructor(). */
void stack_link_init(struct stack_link *stack_link)
{
	_MY_TRACE_STR("stack_link_init()\n");
	memset(stack_link, sizeof(*stack_link), 0);
	stack_init(&stack_link->stack);
	CLASS_OPS_INIT_SUPER(stack_link->stack.ops, stack_ops);
}
