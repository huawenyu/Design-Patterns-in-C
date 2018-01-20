/**
 * stack_hanoi.h  2014-05-02 01:32:58
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
#ifndef __STACK_HANOI_H__
#define __STACK_HANOI_H__

#include "stack.h"

struct stack_hanoi {
	struct stack stack;
	int rejects;
};

void stack_hanoi_init(struct stack_hanoi *, char *);

#endif /* __STACK_HANOI_H__ */