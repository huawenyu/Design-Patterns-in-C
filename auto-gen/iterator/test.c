/**
 *   2014-05-16
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
#include "stack_array.h"
#include "stack_link.h"
#include "stack_array_iter.h"
#include "stack_link_iter.h"

struct datum {
	struct data_node node;
	int val;
};
static struct datum data[] = { {.val=1}, {.val=2}, {.val=3}, {.val=4}, {.val=5} };
static size_t data_sz = sizeof(data)/sizeof(data[0]);

static int test_stack_array(void)
{
	size_t ii;
	struct stack *stack;
	struct stack_array *stack_array;
	struct data_node *node;
	struct datum *a_datum;
	
	stack_array = malloc(sizeof(*stack_array));
	stack_array_init(stack_array);
	stack = &stack_array->stack;
	
	for (ii=0; ii < data_sz; ii++) {
		stack_push(stack, &data[ii].node);
	}

	while (!stack_is_empty(stack)) {
		node = stack_pop(stack);
		a_datum = container_of(node, struct datum, node);
		printf("Pop %d\n", a_datum->val);
	}

	return 0;
}

static int test_stack_array_iter(void)
{
	size_t ii;
	struct stack *stack;
	struct stack_array *stack_array;
	struct iterator *iter;
	struct data_node *node;
	struct datum *a_datum;
	
	stack_array = malloc(sizeof(*stack_array));
	stack_array_init(stack_array);
	stack = &stack_array->stack;
	iter = stack_create_iter(stack);
	
	for (ii=0; ii < data_sz; ii++) {
		stack_push(stack, &data[ii].node);
	}

	iterator_first(iter);
	while (!iterator_is_end(iter)) {
		node = iterator_current(iter);
		a_datum = container_of(node, struct datum, node);
		printf("Iterator %d\n", a_datum->val);
		iterator_next(iter);
	}

	return 0;
}

static int test_stack_link(void)
{
	return 0;
}

static int test_stack_link_iter(void)
{
	return 0;
}

static int test_main_entry(char *output, size_t sz)
{
	test_stack_array();
	test_stack_array_iter();
	test_stack_link();
	test_stack_link_iter();
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test iterator");
}
