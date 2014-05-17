/**
 * stack_array.h  2014-05-16
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
#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include <mycommon.h>
#include <mytrace.h>

#include "stack.h"

#define STACK_ARRAY_MAX 32
/** Add a createIterator() member to the container class */
struct stack_array {
	struct stack stack;
	struct data_node * arr[STACK_ARRAY_MAX]; /** #define STACK_ARRAY_MAX 32 */
	int top;
};

/** constructor(). */
void stack_array_init(struct stack_array *stack_array);

#endif /* __STACK_ARRAY_H__ */
