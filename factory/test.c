
#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <test_suite.h>
#include "pizza_store.h"
#include "pizza_store2.h"
#include "pizza_store3.h"
#include "pizza_simple_factory.h"
#include "pizza_factory.h"
#include "pizza_factory_standard.h"
#include "pizza_factory_greek.h"


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
	struct pizza_store2 *store;
	struct pizza_simple_factory *factory;
	
	factory = malloc(sizeof(*factory));
	pizza_simple_factory_init(factory);

	store = malloc(sizeof(*store));
	pizza_store2_init(store, factory);

	pizza = pizza_store2_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store2_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	pizza_store2_free(store);

	return 0;
}

static int test_factory_method(char *output, size_t sz)
{
	struct pizza *pizza;
	struct pizza_store3 *store;
	struct pizza_factory_standard *factory_canada;
	struct pizza_factory_greek *factory_china;
	
	store = malloc(sizeof(*store));
	pizza_store3_init(store);

	factory_canada = malloc(sizeof(*factory_canada));
	pizza_factory_standard_init(factory_canada);
	pizza_store3_set_factory(store, &factory_canada->factory);

	pizza = pizza_store3_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store3_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	factory_china = malloc(sizeof(*factory_china));
	pizza_factory_greek_init(factory_china);
	pizza_store3_set_factory(store, &factory_china->factory);

	pizza = pizza_store3_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store3_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	pizza_store3_free(store);

	return 0;
}

void factory_test(void);
void factory_test(void)
{
	my_test_suite_add(test_static_factory, "static factory test");
	my_test_suite_add(test_simple_factory, "simple factory test");
	my_test_suite_add(test_factory_method, "factory method test");
}
