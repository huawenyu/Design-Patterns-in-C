/**
 * number.h  2014-05-17
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
#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <mycommon.h>
#include <mytrace.h>

#include "operand.h"

/** <interface> */
struct number {
	struct operand operand;
	int _val;
};

/** constructor(). */
void number_init(struct number *number, int val);

#endif /* __NUMBER_H__ */
