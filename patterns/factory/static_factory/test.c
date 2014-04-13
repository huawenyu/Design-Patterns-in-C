
#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <test_suite.h>
#include "pizza_store.h"

static int test_static_factory(char *output, size_t sz)
{
	struct pizza *pizza;
	pizza = pizza_store_order_pizza("cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store_order_pizza("veggie", pizza_size_normal);
	pizza_free(pizza);

	return 0;
}


void factory_static_test(void);
void factory_static_test(void)
{
	my_test_suite_add(test_static_factory, "Static Factory");
}
