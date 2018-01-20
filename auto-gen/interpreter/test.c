/**
 *   2014-05-17
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
#include <stdio.h>
#include <stdlib.h>

#include <mycommon.h>
#include <myobj.h>
#include <mytrace.h>
#include <test_suite.h>

#include "operand.h"
#include "caculator.h"
#include "context.h"

static int test_main(void)
{
	int i;
	struct operand *op;
	char *postfix;
	static char expr[] = "celsi * 9 / 5 + thirty";
	struct context *ctx;
	char var1[] = "thirty";
	char var2[] = "celsi";

	_MY_TRACE_STR("test::main()\n");
	printf(expr);
	postfix = caculator_convert_to_postfix(expr);
	printf(postfix);
	op = caculator_build_syntax_tree(postfix);
	operand_traverse(op, 1);

	ctx = malloc(sizeof(*ctx));
	context_init(ctx);
	context_put_value(ctx, var1, 30);
	for (i = 0; i <= 100; i += 10) {
		context_put_value(ctx, var2, i);
		printf("C is %d,  F is %d", i, operand_eval(op, ctx));
	}
	return 0;
}

static int test_main_entry(char *output, size_t sz)
{
	test_main();
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test interpreter");
}
