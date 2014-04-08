
#include <stdlib.h>
#include "pizza_store2.h"

struct pizza *pizza_store2_order_pizza(struct pizza_store2 *store,
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

void pizza_store2_init(struct pizza_store2 *store, struct pizza_simple_factory *factory)
{
	store->factory = factory;
}

void pizza_store2_free(struct pizza_store2 *store)
{
	free(store->factory);
}

