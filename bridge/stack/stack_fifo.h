
/**
 * stack_fifo.h  2014-04-30 16:29:05
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
#ifndef __STACK_FIFO_H__
#define __STACK_FIFO_H__

#include "stack.h"

struct stack_fifo {
	struct stack stack;
};

void stack_fifo_init(struct stack_fifo *, char *);

#endif /* __STACK_FIFO_H__ */
