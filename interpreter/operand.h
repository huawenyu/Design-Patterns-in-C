/**
 * operand.h  2014-05-17
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
 * Uses a class hierarchy to represent the grammar given.
 */
#ifndef __OPERAND_H__
#define __OPERAND_H__

#include <mycommon.h>
#include <mytrace.h>

struct context;
struct operand_ops;
/** <interface> */
struct operand {
	struct operand_ops *ops;
};
struct operand_ops {
	void (*traverse)(struct operand *, int level);
	int (*eval)(struct operand *, struct context *ctx);
};

/** constructor(). */
void operand_init(struct operand *operand);

static inline void operand_traverse(struct operand *operand, int level)
{
	operand->ops->traverse(operand, level);
}

static inline int operand_eval(struct operand *operand, struct context *ctx)
{
	return operand->ops->eval(operand, ctx);
}

#endif /* __OPERAND_H__ */
