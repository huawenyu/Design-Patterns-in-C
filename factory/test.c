
#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <test_suite.h>
#include "pizza_store.h"
#include "pizza_store2.h"
#include "pizza_simple_factory.h"

static int test_static_factory(char *output, size_t sz)
{
	struct pizza *pizza;
	pizza = pizza_store_order_pizza("cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store_order_pizza("veggie", pizza_size_normal);
	pizza_free(pizza);

	return 0;
}

static int test_simple_factory(char *output, size_t sz)
{
	struct pizza *pizza;
	struct pizza_store *store;
	struct pizza_simple_factory *factory;
	
	factory = malloc(sizeof(*factory));
	pizza_simple_factory_init(factory);

	store = malloc(sizeof(*store));
	pizza_store_init(store, factory);

	pizza = pizza_store2_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store2_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	return 0;
}

void factory_test(void);
void factory_test(void)
{
	my_test_suite_add(test_static_factory, "static factory test");
	my_test_suite_add(test_simple_factory, "simple factory test");
}
