
/**
 * stack_list.c  2014-04-30 16:29:05
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
#include "stack_list.h"


static void stack_list_ops_push(struct stack_impl *stack_impl, int val)
{
	struct stack_list *list = container_of(stack_impl, typeof(*list), stack_impl);
	printf("stack_list::push()\n");
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
static int stack_list_ops_pop(struct stack_impl *stack_impl)
{
	printf("stack_list::pop()\n");
	return 0;
}
static int stack_list_ops_top(struct stack_impl *stack_impl)
{
	printf("stack_list::top()\n");
	return 0;
}
static int stack_list_ops_is_empty(struct stack_impl *stack_impl)
{
	struct stack_list *list = container_of(stack_impl, typeof(*list), stack_impl);
	printf("stack_list::is_empty()\n");
	return !!list->nodes;
}
static int stack_list_ops_is_full(struct stack_impl *stack_impl)
{
	printf("stack_list::is_full()\n");
	return 0;
}

static struct stack_impl_ops stack_impl_ops = {
	.push = stack_list_ops_push,
	.pop = stack_list_ops_pop,
	.top = stack_list_ops_top,
	.is_empty = stack_list_ops_is_empty,
	.is_full = stack_list_ops_is_full,
};


void stack_list_init(struct stack_list *stack_list, char *stack_impl)
{
	memset(stack_list, sizeof(*stack_list), 0);
	stack_impl_init(&stack_list->stack_impl, stack_impl);
	CLASS_OPS_INIT(stack_list->stack_impl.ops, stack_impl_ops);
}

