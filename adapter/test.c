
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "adapter.h"

static int test_adapter(char *output, size_t sz)
{
	struct adapter *one_adapter;
	struct adaptee *one_adaptee;

	one_adaptee = malloc(sizeof(*one_adaptee));
	if (!one_adaptee) {
		snprintf(output, sz, "malloc one_adaptee fail");
		return 1;
	}
	adaptee_init(one_adaptee);

	one_adapter = malloc(sizeof(*one_adapter));
	if (!one_adapter) {
		snprintf(output, sz, "malloc one_adapter fail");
		return 1;
	}
	adapter_init(one_adapter, one_adaptee);

	target_request(&one_adapter->target);
	return 0;
}

void adapter_test(void);
void adapter_test(void)
{
	my_test_suite_add(test_adapter, "Adapter");
}
