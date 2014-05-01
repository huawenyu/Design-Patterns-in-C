
/**
 * stack_impl.h  2014-04-30 16:29:05
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
#ifndef __STACK_IMPL_H__
#define __STACK_IMPL_H__


struct stack_impl_ops;
struct stack_impl {
	struct stack_impl_ops *ops;
};
struct stack_impl_ops {
	void (*push)(struct stack_impl *, int val);
	int (*pop)(struct stack_impl *);
	int (*top)(struct stack_impl *);
	int (*is_empty)(struct stack_impl *);
	int (*is_full)(struct stack_impl *);
};
void stack_impl_init(struct stack_impl *);


static inline void stack_impl_push(struct stack_impl *stack_impl, int val)
{
	stack_impl->ops->push(stack_impl, val);
}
static inline int stack_impl_pop(struct stack_impl *stack_impl)
{
	return stack_impl->ops->pop(stack_impl);
}
static inline int stack_impl_top(struct stack_impl *stack_impl)
{
	return stack_impl->ops->top(stack_impl);
}
static inline int stack_impl_is_empty(struct stack_impl *stack_impl)
{
	return stack_impl->ops->is_empty(stack_impl);
}
static inline int stack_impl_is_full(struct stack_impl *stack_impl)
{
	return stack_impl->ops->is_full(stack_impl);
}

#endif /* __STACK_IMPL_H__ */
