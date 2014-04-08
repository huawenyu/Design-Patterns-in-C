
#include <string.h>
#include "pizza_store2.h"
#include "cheese_pizza.h"
#include "veggie_pizza.h"

struct pizza *pizza_store2_order_pizza(struct pizza_store *store,
		const char *name, enum pizza_size_type size)
{
	struct pizza *pizza;

	pizza = pizza_simple_factory_create(store->factory, name, size);
	if (!pizza)
		return 0;

	pizza_prepare(pizza);
	pizza_bake(pizza);
	pizza_cut(pizza);
	pizza_box(pizza);

	return pizza;
}

void pizza_store_init(struct pizza_store *store, struct pizza_simple_factory *factory)
{
	store->factory = factory;
}

