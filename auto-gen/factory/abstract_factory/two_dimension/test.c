
#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <test_suite.h>
#include "pizza_store3.h"
#include "pizza_factory.h"
#include "pizza_factory_standard.h"
#include "pizza_factory_greek.h"

static int test_factory_method(char *output, size_t sz)
{
	struct pizza *pizza;
	struct pizza_store3 *store;
	struct pizza_factory_standard *factory_standard;
	struct pizza_factory_greek *factory_greek;
	
	store = malloc(sizeof(*store));
	pizza_store3_init(store);

	factory_standard = malloc(sizeof(*factory_standard));
	pizza_factory_standard_init(factory_standard);
	pizza_store3_set_factory(store, &factory_standard->factory);

	pizza = pizza_store3_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store3_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	factory_greek = malloc(sizeof(*factory_greek));
	pizza_factory_greek_init(factory_greek);
	pizza_store3_set_factory(store, &factory_greek->factory);

	pizza = pizza_store3_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store3_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	pizza_store3_free(store);

	return 0;
}

void factory_method_test(void);
void factory_method_test(void)
{
	my_test_suite_add(test_factory_method, "Factory Method");
}
