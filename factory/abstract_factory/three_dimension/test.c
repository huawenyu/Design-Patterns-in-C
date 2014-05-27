
#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <test_suite.h>
#include "../two_dimension/pizza_store3.h"
#include "../two_dimension/pizza_factory.h"
#include "pizza_factory_standard_v2.h"
#include "pizza_ingredient_factory_organic.h"

static int test_abstrace_factory(char *output, size_t sz)
{
	struct pizza *pizza;
	struct pizza_store3 *store;
	struct pizza_factory_standard_v2 *factory_standard;
	struct pizza_ingredient_factory_organic factory_organic;
	
	store = malloc(sizeof(*store));
	pizza_store3_init(store);

	pizza_ingredient_factory_organic_init(&factory_organic);

	factory_standard = malloc(sizeof(*factory_standard));
	pizza_factory_standard_v2_init(factory_standard, &factory_organic.factory);
	pizza_store3_set_factory(store, &factory_standard->factory);

	pizza = pizza_store3_order_pizza(store, "cheese", pizza_size_large);
	pizza_free(pizza);

	pizza = pizza_store3_order_pizza(store, "veggie", pizza_size_normal);
	pizza_free(pizza);

	pizza_store3_free(store);

	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_abstrace_factory, "Abstract Factory : two dimension");
}
