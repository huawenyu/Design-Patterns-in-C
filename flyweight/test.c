/**
 *   2014-05-19
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
#include "character_factory.h"
#include "character_a.h"
#include "character_b.h"
#include "character_c.h"

// Build a document with text
static int test_main(void)
{
	size_t i;
	int point_size = 10; // extrinsic state
	char document[] = "AACCBBCB";
	struct character *val_char;
	struct character_factory *fac;
	_MY_TRACE_STR("test::main()\n");

	fac = malloc(sizeof(*fac));
	character_factory_init(fac);

	for (i=0; i < sizeof(document)/sizeof(document[0]); i++) {
		point_size++;
		val_char = character_factory_get_character(fac, document[i]);
		if (val_char) {
			character_display(val_char, point_size);
		}
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
	my_test_suite_add(test_main_entry, "Test flyweight");
}
