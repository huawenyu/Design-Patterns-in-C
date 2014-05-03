
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "main_entry.h"

static int test_main_entry(char *output, size_t sz)
{
	main_entry_main_entry();
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, main_entry_get_name());
}
