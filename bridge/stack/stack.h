/**
 * stack.h  2014-05-02 01:32:58
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
#ifndef __STACK_H__
#define __STACK_H__

#include "stack_impl.h"

struct stack_ops;

struct stack {
	struct stack_ops *ops;
	struct stack_impl * _impl;
};
struct stack_ops {
	void (*_destructor)(struct stack *); /** called by free(): put resources, forward to super. */
	void (*free)(struct stack *); /** free memory after call destructor(). */
	void (*push)(struct stack *, int val);
	int (*pop)(struct stack *);
	int (*top)(struct stack *);
	int (*is_empty)(struct stack *);
	int (*is_full)(struct stack *);
	void (*free)(struct stack *);
	struct stack_ops *super;
};
void stack_init(struct stack *, const char *);

/** called by free(): put resources, forward to super. */
static inline void stack__destructor(struct stack *stack)
{
	stack->ops->_destructor(stack);
}
/** free memory after call destructor(). */
static inline void stack_free(struct stack *stack)
{
	stack->ops->free(stack);
}

static inline void stack_push(struct stack *stack, int val)
{
	stack->ops->push(stack, val);
}

static inline int stack_pop(struct stack *stack)
{
	return stack->ops->pop(stack);
}

static inline int stack_top(struct stack *stack)
{
	return stack->ops->top(stack);
}

static inline int stack_is_empty(struct stack *stack)
{
	return stack->ops->is_empty(stack);
}

static inline int stack_is_full(struct stack *stack)
{
	return stack->ops->is_full(stack);
}

static inline void stack_free(struct stack *stack)
{
	stack->ops->free(stack);
}

#endif /* __STACK_H__ */