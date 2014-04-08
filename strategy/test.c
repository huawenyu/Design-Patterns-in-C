
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test_bed.h"

static int test()
{
	struct test_bed test;
	int ii, answer[] = {1,2,1,1,2};
	char *retstr = "left,right,left,left,right";

	test_bed_init(&test);
	printf("output should be: %s\n", retstr);
	for (ii=0; ii < sizeof(answer)/sizeof(answer[0]); ++ii) {
		test.ops->set_strategy(&test, answer[ii]);
		test.ops->do_it(&test);
	}
	return 0;
}

void strategy_test()
{
	my_test_suite_add(test, "strategy test");
}
