
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TestBed.h"

static int test()
{
	struct test_bed test;
	int answer;

	test_bed_init(&test);
	printf("Exit(0) Left(1) Right(2): \n");
	scanf("%d", &answer);
	while (answer) {
		test.ops->set_strategy(&test, answer);
		test.ops->do_it(&test);
		printf("Exit(0) Left(1) Right(2): \n");
		scanf("%d", &answer);
	}
	return 0;
}

void strategy_test()
{
	my_test_suite_add(test, "strategy test");
}
