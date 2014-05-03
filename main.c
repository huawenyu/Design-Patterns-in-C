#include <stdio.h>
#include <stdlib.h>
#include <mytrace.h>
#include "test_suite.h"

int main(void)
{
	_MY_TRACE_INIT_; /* support trace, remove if no-trace needed */

	my_test_suite_open();
	my_test_suite_run_all(MY_TEST_SUITE_FLAG_VERBOSE);
	my_test_suite_close();

	return 0;
}

