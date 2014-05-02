/**
 * stack_hanoi.c  2014-05-02 01:32:58
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
#include "stack_hanoi.h"

static void stack_hanoi_ops_push(struct stack *stack, int val)
{
	struct stack_hanoi *hanoi = container_of(stack, typeof(*hanoi), stack);
	printf("stack_hanoi::push()\n");
	if (!stack_impl_is_empty(stack->_impl) && val > stack_impl_top(stack->_impl)) {
		hanoi->rejects ++;
	}
	else {
		stack_impl_push(stack->_impl, val);
	}
}

static struct stack_ops stack_ops = {
	.push = stack_hanoi_ops_push,
};


void stack_hanoi_init(struct stack_hanoi *stack_hanoi, char *stack_impl)
{
	memset(stack_hanoi, sizeof(*stack_hanoi), 0);
	stack_init(&stack_hanoi->stack, stack_impl);
	CLASS_OPS_INIT_WITH_SUPER(stack_hanoi->stack.ops, stack_ops, super);
	stack_hanoi->rejects = 0;
}