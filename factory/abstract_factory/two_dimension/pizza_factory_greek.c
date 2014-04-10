
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */
#include <myobj.h>
#include "greek_cheese_pizza.h"
#include "greek_veggie_pizza.h"
#include "pizza_factory_greek.h"

static struct pizza *factory_greek_create(struct pizza_factory *factory,
		const char *name, enum pizza_size_type size)
{
	struct pizza *pizza = 0;
	struct greek_cheese_pizza *cheese;
	struct greek_veggie_pizza *veggie;

	if (!strcmp(name, "cheese")) {
		cheese = malloc(sizeof(*cheese));
		if (!cheese)
			return 0;

		greek_cheese_pizza_init(cheese, size);
		pizza = &cheese->pizza;
	}
	else if (!strcmp(name, "veggie")) {
		veggie = malloc(sizeof(*veggie));
		if (!veggie)
			return 0;

		greek_veggie_pizza_init(veggie, size);
		pizza = &veggie->pizza;
	}
	return pizza;
}

static void factory_greek_free(struct pizza_factory *factory)
{
	struct pizza_factory_greek *factory_greek =
		container_of(factory, typeof(*factory_greek), factory);
	free(factory_greek);
}

static struct pizza_factory_ops ops = {
	.create = factory_greek_create,
	.free = factory_greek_free,
};

void pizza_factory_greek_init(struct pizza_factory_greek *factory)
{
	pizza_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}

