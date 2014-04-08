
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */
#include <myobj.h>
#include "cheese_pizza.h"
#include "veggie_pizza.h"
#include "pizza_factory_style_canada.h"

static struct pizza *factory_style_canada_create(struct pizza_factory *factory,
		const char *name, enum pizza_size_type size)
{
	struct pizza *pizza = 0;
	struct cheese_pizza *cheese;
	struct veggie_pizza *veggie;

	if (!strcmp(name, "cheese")) {
		cheese = malloc(sizeof(*cheese));
		if (!cheese)
			return 0;

		cheese_pizza_init(cheese, size);
		pizza = &cheese->pizza;
	}
	else if (!strcmp(name, "veggie")) {
		veggie = malloc(sizeof(*veggie));
		if (!veggie)
			return 0;

		veggie_pizza_init(veggie, size);
		pizza = &veggie->pizza;
	}
	return pizza;
}

static void factory_style_candada_free(struct pizza_factory *factory)
{
	struct pizza_factory_style_canada *factory_canada =
		container_of(factory, typeof(*factory_canada), factory);
	free(factory_canada);
}


static struct pizza_factory_ops ops = {
	.create = factory_style_canada_create,
	.free = factory_style_candada_free,
};

void pizza_factory_style_canada_init(struct pizza_factory_style_canada *factory)
{
	pizza_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}

