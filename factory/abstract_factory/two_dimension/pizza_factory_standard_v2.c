
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */
#include <myobj.h>
#include "cheese_pizza_v2.h"
#include "veggie_pizza_v2.h"
#include "pizza_factory_standard_v2.h"

static struct pizza *factory_standard_v2_create(struct pizza_factory *factory,
		const char *name, enum pizza_size_type size)
{
	struct pizza_factory_standard_v2 *factory_standard =
			container_of(factory, typeof(*factory_standard), factory);
	struct pizza *pizza = 0;
	struct cheese_pizza_v2 *cheese;
	struct veggie_pizza_v2 *veggie;

	if (!strcmp(name, "cheese")) {
		cheese = malloc(sizeof(*cheese));
		if (!cheese)
			return 0;

		cheese_pizza_v2_init(cheese, size, factory_standard->ingredient_factory);
		pizza = &cheese->pizza.pizza;
	}
	else if (!strcmp(name, "veggie")) {
		veggie = malloc(sizeof(*veggie));
		if (!veggie)
			return 0;

		veggie_pizza_v2_init(veggie, size, factory_standard->ingredient_factory);
		pizza = &veggie->pizza.pizza;
	}
	return pizza;
}

static void factory_standard_v2_free(struct pizza_factory *factory)
{
	struct pizza_factory_standard_v2 *factory_standard =
		container_of(factory, typeof(*factory_standard), factory);
	free(factory_standard);
}


static struct pizza_factory_ops ops = {
	.create = factory_standard_v2_create,
	.free = factory_standard_v2_free,
};

void pizza_factory_standard_v2_init(struct pizza_factory_standard_v2 *factory,
		struct pizza_ingredient_factory *ingredient_factory)
{
	pizza_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
	factory->ingredient_factory = ingredient_factory;
}

