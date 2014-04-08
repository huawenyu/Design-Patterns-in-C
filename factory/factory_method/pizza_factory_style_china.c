
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */
#include <myobj.h>
#include "china_cheese_pizza.h"
#include "china_veggie_pizza.h"
#include "pizza_factory_style_china.h"

static struct pizza *factory_style_china_create(struct pizza_factory *factory,
		const char *name, enum pizza_size_type size)
{
	struct pizza *pizza = 0;
	struct china_cheese_pizza *cheese;
	struct china_veggie_pizza *veggie;

	if (!strcmp(name, "cheese")) {
		cheese = malloc(sizeof(*cheese));
		if (!cheese)
			return 0;

		china_cheese_pizza_init(cheese, size);
		pizza = &cheese->pizza;
	}
	else if (!strcmp(name, "veggie")) {
		veggie = malloc(sizeof(*veggie));
		if (!veggie)
			return 0;

		china_veggie_pizza_init(veggie, size);
		pizza = &veggie->pizza;
	}
	return pizza;
}

static void factory_style_china_free(struct pizza_factory *factory)
{
	struct pizza_factory_style_china *factory_china =
		container_of(factory, typeof(*factory_china), factory);
	free(factory_china);
}

static struct pizza_factory_ops ops = {
	.create = factory_style_china_create,
	.free = factory_style_china_free,
};

void pizza_factory_style_china_init(struct pizza_factory_style_china *factory)
{
	pizza_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}

