
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <test_suite.h>
#include "test_bed.h"

static int strategy_test(char *output, size_t sz)
{
	struct test_bed test;
	unsigned int ii, answer[] = {1,2,1,1,2};
	const char *retstr = "left,right,left,left,right";

	test_bed_init(&test);
	printf("output should be: \n%s\n", retstr);
	for (ii=0; ii < sizeof(answer)/sizeof(answer[0]); ++ii) {
		test.ops->set_strategy(&test, answer[ii]);
		test.ops->do_it(&test);
	}
	printf("\n");
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(strategy_test, "Test Strategy");
}
