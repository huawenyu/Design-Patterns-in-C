/**
 * operand.c  2014-05-17
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
#include "operand.h"

static void operand_ops_traverse(struct operand *operand, int level)
{
	_MY_TRACE_STR("operand::traverse()\n");
}

static int operand_ops_eval(struct operand *operand, struct context *ctx)
{
	_MY_TRACE_STR("operand::eval()\n");
	return 0;
}
static struct operand_ops operand_ops = {
	.traverse = operand_ops_traverse,
	.eval = operand_ops_eval,
};

/** constructor(). */
void operand_init(struct operand *operand)
{
	_MY_TRACE_STR("operand_init()\n");
	memset(operand, sizeof(*operand), 0);
	operand->ops = &operand_ops;
}