/**
 * caculator.c  2014-05-17
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
#include <ctype.h>

#include <mycommon.h>
#include <util.h>

#include "stack.h"
#include "caculator.h"

STACK_IMPL(stack, char, 128);
STACK_IMPL(stack_op, struct operand *, 128);

/** constructor(). */
void caculator_init(struct caculator *caculator)
{
	_MY_TRACE_STR("caculator_init()\n");
	memset(caculator, sizeof(*caculator), 0);
}

/** return bool */
int caculator_precedence(char a, char b)
{
	_MY_TRACE_STR("caculator::precedence()\n");
	if (a == '(')
		return 0;
	if (a == ')' && b == '(')
	{
		printf(")-(");
		return 0;
	}
	if (b == '(')
		return 0;
	if (b == ')')
		return 1;
	if ((a == '*' || a == '/')  && (b == '+' || b == '-'))
		return 1;
	if ((a == '*' || a == '/')  && (b == '*' || b == '/'))
		return 1;
	if ((a == '+' || a == '-')  && (b == '+' || b == '-'))
		return 1;
	return 0;
}
/** convert expr from in-fix to post-fix */
char * caculator_convert_to_postfix(char *expr)
{
	int ii;
	int token_i = 0;
	char *tokens[128];

	char opers[] = "+-*/()";
	char top_sym = '+';
	char char2str[2] = {0};
	int is_empty;
	static char out_buf[128] = {0};

	_MY_TRACE_STR("caculator::convert_to_postfix()\n");

	tokens[token_i] = strtok(expr, " ");
	while (tokens[token_i]) {
		tokens[++token_i] = strtok(NULL, " ");
	}

	for (ii=0; ii < token_i; ii++) {
		if (strchr(opers, tokens[ii][0]) == NULL) {
			strncat(out_buf, tokens[ii], sizeof(out_buf));
			strncat(out_buf, " ", sizeof(out_buf));
		}
		else {
			while (!(is_empty=stack_is_empty())
			       && caculator_precedence(top_sym=stack_pop(), tokens[ii][0])) {
				char2str[0] = top_sym;
				strncat(out_buf, char2str, sizeof(out_buf));
				strncat(out_buf, " ", sizeof(out_buf));
			}
			if (! is_empty)
				stack_push(top_sym);
			if (is_empty || tokens[ii][0] != ')')
				stack_push(tokens[ii][0]);
			else
				top_sym = stack_pop();
		}
	}

	while (!stack_is_empty()) {
		char2str[0] = stack_pop();
		strncat(out_buf, char2str, sizeof(out_buf));
		strncat(out_buf, " ", sizeof(out_buf));
	}

	return out_buf;
}

struct operand * caculator_build_syntax_tree(char *tree)
{
	int i;
	char opers[] = "+-*/";
	int token_i = 0;
	char *tokens[128];

	_MY_TRACE_STR("caculator::build_syntax_tree()\n");
	tokens[token_i] = strtok(tree, " ");
	while (tokens[token_i]) {
		tokens[++token_i] = strtok(NULL, " ");
	}
	for (i = 0; i < token_i; i++) {
		// If token is a number or variable
		if (strchr(opers, tokens[i][0]) == NULL) {
			if (is_numeric(tokens[i])) {
				struct number *num;
				num = malloc(sizeof(*num));
				number_init(num, atoi(tokens[i]));
				stack_op_push(&num->operand);
			}
			else {
				struct variable *var;
				var = malloc(sizeof(*var));
				variable_init(var, tokens[i]);
				stack_op_push(&var->operand);
			}
		}
		else {// If token is an operator
			struct expression *expr;
			expr = malloc(sizeof(*expr));
			expression_init(expr, tokens[i][0]);
			expr->_right = stack_op_pop();
			expr->_left = stack_op_pop();
			stack_op_push(&expr->operand);
		}
	}
	return stack_op_pop();
}
