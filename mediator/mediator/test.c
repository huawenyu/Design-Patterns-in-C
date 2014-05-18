/**
 *   2014-05-18
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
#include "widget_one.h"
#include "widget_two.h"
#include "mediator.h"

static int test_main(void)
{
	struct mediator *mediator;
	struct widget_one *one;
	struct widget_two *two;
	char msg[] = "Hello world";

	_MY_TRACE_STR("test::main()\n");
	mediator = malloc(sizeof(*mediator));
	mediator_init(mediator);

	one = malloc(sizeof(*one));
	widget_one_init(one, mediator);
	mediator_register_widget_one(mediator, one);

	two = malloc(sizeof(*two));
	widget_two_init(two, mediator);
	mediator_register_widget_two(mediator, two);

	printf("widget_one: %s\n", widget_one_talk(one, msg));
	
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
	my_test_suite_add(test_main_entry, "Test mediator");
}
