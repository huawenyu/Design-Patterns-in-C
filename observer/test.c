/**
 *   2014-05-14
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
#include "database.h"
#include "view.h"

static int test_main(void)
{
	struct view *v;
	struct database *db;
	char operation[32] = "delete";
	char record[32] = "record 1";
	_MY_TRACE_STR("test::main()\n");

	v = malloc(sizeof(*v));
	view_init(v);
	db = malloc(sizeof(*db));
	database_init(db);

	subject_register_observer(&db->subject, &v->observer);
	database_edit_record(db, operation, record);

	subject_remove_observer(&db->subject, &v->observer);
	database_edit_record(db, operation, record);
	
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
	my_test_suite_add(test_main_entry, "Test observer");
}
