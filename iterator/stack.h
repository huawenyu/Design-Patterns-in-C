/**
 * stack.h  2014-05-16
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
#ifndef __STACK_H__
#define __STACK_H__

#include <mycommon.h>
#include <mytrace.h>

#include "iterator.h"
		
#include "data_node.h"

struct stack_ops;
/** Add a createIterator() member to the container class */
struct stack {
	struct stack_ops *ops;
};
struct stack_ops {
	void (*push)(struct stack *, struct data_node *node);
	struct data_node * (*pop)(struct stack *);
	int (*is_empty)(struct stack *); /** return bool */
	int (*is_full)(struct stack *); /** return bool */
	struct iterator * (*create_iter)(struct stack *);
	struct stack_ops *__super;
};

/** constructor(). */
void stack_init(struct stack *stack);

static inline void stack_push(struct stack *stack, struct data_node *node)
{
	stack->ops->push(stack, node);
}

static inline struct data_node * stack_pop(struct stack *stack)
{
	return stack->ops->pop(stack);
}
/** return bool */
static inline int stack_is_empty(struct stack *stack)
{
	return stack->ops->is_empty(stack);
}
/** return bool */
static inline int stack_is_full(struct stack *stack)
{
	return stack->ops->is_full(stack);
}

static inline struct iterator * stack_create_iter(struct stack *stack)
{
	return stack->ops->create_iter(stack);
}

#endif /* __STACK_H__ */