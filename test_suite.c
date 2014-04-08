
#include <ulist.h>  /* struct list_head */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memset */
#include <stdio.h>  /* printf */
#include "test_suite.h"

/* my test suite */
struct my_test_suite;
static void test_add(struct my_test_suite *suite, test_case_fp, const char *note);
static void test_run(struct my_test_suite *suite, unsigned int flags);

struct my_test_suite_ops {
	void (*add)(struct my_test_suite *, test_case_fp, const char *note);
	void (*run)(struct my_test_suite *, unsigned int flags);
} static test_ops = {
	.add = test_add,
	.run = test_run,
};

struct my_test_suite {
	struct my_test_suite_ops *ops;
	struct list_head test_cases;
	char *name;
	int total, fail, pos;
	int init;
} static my_test_suite = {
	.name = "Design Pattern TestSuite",
};

void my_test_suite_init(struct my_test_suite *suite)
{
	if (!suite->init) {
		suite->init = 1;
		INIT_LIST_HEAD(&suite->test_cases);
		suite->ops = &test_ops;
	}
}

struct my_test_case {
	struct list_head suite;
	test_case_fp test_case;
	int rtn;
	char msg[128];
	char note[32];
};

static void test_add(struct my_test_suite *suite, test_case_fp test_case_func, const char *note)
{
	struct my_test_case *test_case;

#ifndef MY_RUN_TEST_FROM_CLI
	return;
#endif

	if (!test_case_func)
		return;
	test_case = malloc(sizeof(*test_case));
	if (!test_case)
		return;
	memset(test_case, 0, sizeof(*test_case));
	INIT_LIST_HEAD(&test_case->suite);
	test_case->test_case = test_case_func;
	strncpy(test_case->note, note, sizeof(test_case->note)-1);
	list_add_tail(&test_case->suite, &suite->test_cases);
	suite->total += 1;
}

static void test_run(struct my_test_suite *suite, unsigned int flags)
{
	struct my_test_case *test_case;
	int pos = 0;
	int all_finish = 1;

	if (!suite->init)
		return;
	MY_DEBUG(MY_DEBUG_TEST "\n=TESTSUITE=BEGIN[%s] total %d fail %d at %d\n",
		suite->name, suite->total, suite->fail, suite->pos);

	if (flags & MY_TEST_SUITE_FLAG_RESTART)
		suite->pos = 0;
	suite->fail = 0;
	list_for_each_entry(test_case, &suite->test_cases, suite) {
		pos ++;
		if (pos < suite->pos)
			continue;
		suite->pos = pos;
		test_case->msg[0] = '\0';

		if (flags & MY_TEST_SUITE_FLAG_DRYRUN)
			test_case->rtn = 0;
		else
			test_case->rtn = test_case->test_case(test_case->msg, sizeof(test_case->msg));

		if (test_case->rtn != 0)
			suite->fail += 1;

		if (flags & (MY_TEST_SUITE_FLAG_VERBOSE|MY_TEST_SUITE_FLAG_DRYRUN)
			|| test_case->rtn != 0) {
			MY_DEBUG(MY_DEBUG_TEST
				"=TESTSUITE= %s %d\t%s\t%s\n",
				test_case->rtn==0 ? "OK":"X", test_case->rtn,
				test_case->note, test_case->msg);
		}

		if (!(flags & MY_TEST_SUITE_FLAG_FAIL_CONT)
			&& test_case->rtn != 0) {
			all_finish = 0;
			break;
		}
	}
	MY_DEBUG(MY_DEBUG_TEST "\n=TESTSUITE= END [%s] total %d fail %d at %d\n",
		suite->name, suite->total, suite->fail, suite->pos);

	if (all_finish) {
		suite->pos = 0;
		suite->fail = 0;
	}
}

void my_test_suite_add(test_case_fp test_case, const char *note)
{
	my_test_suite.ops->add(&my_test_suite, test_case, note);
}

void my_test_suite_run_all(unsigned int flags)
{
	my_test_suite.ops->run(&my_test_suite, flags);
}

void my_test_suite_open()
{
	my_test_suite_init(&my_test_suite);

	extern void strategy_test(); strategy_test();
	extern void chain_of_responsibility_test(); chain_of_responsibility_test();
}

void my_test_suite_close()
{
	struct my_test_case *test_case, *n;
	list_for_each_entry_safe(test_case, n, &my_test_suite.test_cases, suite) {
		list_del(&test_case->suite);
		free(test_case);
	}
}
