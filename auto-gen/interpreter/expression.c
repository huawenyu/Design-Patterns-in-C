/**
 * expression.c  2014-05-17
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
#include "expression.h"

static void expression_ops_traverse(struct operand *operand, int level)
{
	struct expression *a_expression = container_of(operand, typeof(*a_expression), operand);
	
	_MY_TRACE_STR("expression::traverse()\n");
	operand_traverse(a_expression->_left, level + 1);
	printf("%d%c%d ", level, a_expression->_oper, level);
	operand_traverse(a_expression->_right, level + 1);
}

static int expression_ops_eval(struct operand *operand, struct context *ctx)
{
	struct expression *a_expression = container_of(operand, typeof(*a_expression), operand);
	int result = 0, a, b;
	_MY_TRACE_STR("expression::eval()\n");

	a = operand_eval(a_expression->_left, ctx);
	b = operand_eval(a_expression->_right, ctx);

	switch (a_expression->_oper) {
		case '+': result = a + b; break;
		case '-': result = a - b; break;
		case '*': result = a * b; break;
		case '/': result = a / b; break;
		default: break;
	}
	return result;
}

static struct operand_ops operand_ops = {
	.traverse = expression_ops_traverse,
	.eval = expression_ops_eval,
};

/** constructor(). */
void expression_init(struct expression *expression, char oper)
{
	_MY_TRACE_STR("expression_init()\n");
	memset(expression, sizeof(*expression), 0);
	operand_init(&expression->operand);
	CLASS_OPS_INIT(expression->operand.ops, operand_ops);
	expression->_oper = oper;
}
