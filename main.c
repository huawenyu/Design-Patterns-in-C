#include <stdio.h>
#include <stdlib.h>
#include "test_suite.h"

int main()
{
	my_test_suite_open();
	my_test_suite_run_all(MY_TEST_SUITE_FLAG_VERBOSE);
	my_test_suite_close();

	return 0;
}

