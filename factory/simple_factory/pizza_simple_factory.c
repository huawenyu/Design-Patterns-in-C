
#include <string.h>
#include "cheese_pizza.h"
#include "veggie_pizza.h"
#include "pizza_simple_factory.h"

static struct pizza *simple_factory_create(const char *name, enum pizza_size_type size)
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

static struct pizza_simple_factory_ops ops = {
	.create = simple_factory_create,
};

void pizza_simple_factory_init(struct pizza_simple_factory *factory)
{
	factory->ops = &ops;
}

