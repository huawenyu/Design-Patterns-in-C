
#include <stdio.h>
#include <stdlib.h>
#include "pizza_store.h"

static int test(void)
{
	struct pizza *pizza;
	pizza = pizza_store_order_pizza("cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store_order_pizza("veggie", pizza_size_normal);
	pizza_free(pizza);

	return 0;
}

void static_factory_test()
{
	my_test_suite_add(test, "static factory test");
}
