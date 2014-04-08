
#include <string.h>
#include "pizza_store3.h"

struct pizza *pizza_store3_order_pizza(struct pizza_store3 *store,
		const char *name, enum pizza_size_type size)
{
	struct pizza *pizza;

	pizza = pizza_factory_create(store->factory, name, size);
	if (!pizza)
		return 0;

	pizza_prepare(pizza);
	pizza_bake(pizza);
	pizza_cut(pizza);
	pizza_box(pizza);

	return pizza;
}

void pizza_store3_init(struct pizza_store3 *store)
{
	store->factory = 0;
}

void pizza_store3_free(struct pizza_store3 *store)
{
	if (store->factory)
		pizza_factory_free(store->factory);
}

void pizza_store3_set_factory(struct pizza_store3 *store, struct pizza_factory *factory)
{
	if (store->factory)
		pizza_factory_free(store->factory);
	store->factory = factory;
}
