
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "bridge.h"

static int test_stack(char *output, size_t sz)
{
	bridge_main_entry();
	return 0;
}

void bridge_stack_test(void);
void bridge_stack_test(void)
{
	my_test_suite_add(test_stack, "Bridge Stack");
}
