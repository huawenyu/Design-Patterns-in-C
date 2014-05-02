/**
 * stack_impl_list.h  2014-05-02 01:32:58
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
#ifndef __STACK_IMPL_LIST_H__
#define __STACK_IMPL_LIST_H__

#include "node.h"
#include "stack_impl.h"

struct stack_impl_list {
	struct stack_impl stack_impl;
	struct node * nodes;
};

void stack_impl_list_init(struct stack_impl_list *);

#endif /* __STACK_IMPL_LIST_H__ */