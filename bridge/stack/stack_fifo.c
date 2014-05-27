/**
 * stack_fifo.c  2014-05-02 01:32:58
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
#include "stack_fifo.h"
#include "stack_impl_list.h"

static int stack_fifo_ops_pop(struct stack *stack)
{
	int rtn;
	struct stack_impl_list *list;
	printf("stack_fifo::pop()\n");
	list = malloc(sizeof(*list));
	if (!list)
		return -1; /* assume the data eg 0 */
	stack_impl_list_init(list);
	while (!stack_is_empty(stack)) {
		stack_impl_push(&list->stack_impl, CLASS_SUPER_RTN(stack, pop, int));
	}
	rtn = stack_impl_pop(&list->stack_impl);
	while (!stack_impl_is_empty(&list->stack_impl)) {
		CLASS_SUPER(stack, push, stack_impl_pop(&list->stack_impl));
	}
	return rtn;
}

static struct stack_ops stack_ops = {
	.pop = stack_fifo_ops_pop,
};


void stack_fifo_init(struct stack_fifo *stack_fifo, char *stack_impl)
{
	memset(stack_fifo, sizeof(*stack_fifo), 0);
	stack_init(&stack_fifo->stack, stack_impl);
	CLASS_OPS_INIT_SUPER(stack_fifo->stack.ops, stack_ops);
}
