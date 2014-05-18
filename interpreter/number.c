/**
 * number.c  2014-05-17
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "number.h"

static void number_ops_traverse(struct operand *operand, int level)
{
	struct number *a_number = container_of(operand, typeof(*a_number), operand);
	
	_MY_TRACE_STR("number::traverse()\n");
	printf("%d ", a_number->_val);
}

static int number_ops_eval(struct operand *operand, struct context *ctx)
{
	struct number *a_number = container_of(operand, typeof(*a_number), operand);
	
	_MY_TRACE_STR("number::eval()\n");
	return a_number->_val;
}

static struct operand_ops operand_ops = {
	.traverse = number_ops_traverse,
	.eval = number_ops_eval,
};

/** constructor(). */
void number_init(struct number *number, int val)
{
	_MY_TRACE_STR("number_init()\n");
	memset(number, sizeof(*number), 0);
	operand_init(&number->operand);
	CLASS_OPS_INIT(number->operand.ops, operand_ops);
	number->_val = val;
}
