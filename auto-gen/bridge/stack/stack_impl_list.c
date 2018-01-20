/**
 * stack_impl_list.c  2014-05-02 01:32:58
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
#include "stack_impl_list.h"

/** called by free(): put resources, forward to super. */
static void stack_impl_list_ops__destructor(struct stack_impl *stack_impl)
{
	printf("stack_impl_list::_destructor()\n");
	/** pseudocode: careful about mult-inherit
	... do_something() to put resources ...
	CLASS_SUPER(stack_impl_list, _destructor);
	*/
	CLASS_SUPER(stack_impl, _destructor);
}
/** free memory after call destructor(). */
static void stack_impl_list_ops_free(struct stack_impl *stack_impl)
{
	struct stack_impl_list *l_stack_impl_list = container_of(stack_impl, typeof(*l_stack_impl_list), stack_impl);
	/** pseudocode: careful about mult-inherit
	struct stack_impl_list *l_stack_impl_list = container_of(stack_impl_list, typeof(*l_stack_impl_list), stack_impl);
	stack_impl__destructor(stack_impl_list);
	free(l_stack_impl_list);
	*/
	stack_impl__destructor(stack_impl);
	printf("stack_impl_list::free()\n");
	free(l_stack_impl_list);
}

static void stack_impl_list_ops_push(struct stack_impl *stack_impl, int val)
{
	struct stack_impl_list *list = container_of(stack_impl, typeof(*list), stack_impl);
	printf("stack_impl_list::push()\n");
	if (list->nodes) {
		struct node *prev = list->nodes->prev;
		struct node *curr = malloc(sizeof(*curr));
		prev->next = curr;
		curr->next = list->nodes;
		curr->prev = prev;
	}
	else {
		list->nodes = malloc(sizeof(*list->nodes));
		node_init(list->nodes, val);
	}
}

static int stack_impl_list_ops_pop(struct stack_impl *stack_impl)
{
	printf("stack_impl_list::pop()\n");
	return 0;
}

static int stack_impl_list_ops_top(struct stack_impl *stack_impl)
{
	printf("stack_impl_list::top()\n");
	return 0;
}

static int stack_impl_list_ops_is_empty(struct stack_impl *stack_impl)
{
	struct stack_impl_list *list = container_of(stack_impl, typeof(*list), stack_impl);
	printf("stack_impl_list::is_empty()\n");
	return !!list->nodes;
}

static int stack_impl_list_ops_is_full(struct stack_impl *stack_impl)
{
	printf("stack_impl_list::is_full()\n");
	return 0;
}

static struct stack_impl_ops stack_impl_ops = {
	._destructor = stack_impl_list_ops__destructor,
	.free = stack_impl_list_ops_free,
	.push = stack_impl_list_ops_push,
	.pop = stack_impl_list_ops_pop,
	.top = stack_impl_list_ops_top,
	.is_empty = stack_impl_list_ops_is_empty,
	.is_full = stack_impl_list_ops_is_full,
};

void stack_impl_list_init(struct stack_impl_list *stack_impl_list)
{
	memset(stack_impl_list, sizeof(*stack_impl_list), 0);
	stack_impl_init(&stack_impl_list->stack_impl);
	CLASS_OPS_INIT_SUPER(stack_impl_list->stack_impl.ops, stack_impl_ops);
}
