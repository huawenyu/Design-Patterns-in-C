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
#include "me.h"

static int test_main(void)
{
	struct me *me;
	_MY_TRACE_STR("test::main()\n");
	me = malloc(sizeof(*me));
	me_init(me);

	A_do_this(&me->A_B1.A);
	A_do_that(&me->A_B1.A);

	A_do_this(&me->A_B2.A);
	A_do_that(&me->A_B2.A);

	A_do_this(&me->A_B3.A);
	A_do_that(&me->A_B3.A);

	M_put_here(&me->M_N.M);
	M_put_there(&me->M_N.M);

	P_jump_up(&me->P_Q.P);
	P_jump_down(&me->P_Q.P);

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
	my_test_suite_add(test_main_entry, "Test mult_inherit");
}
