
#include <stdio.h>
#include <myobj.h>

#include "pizza_ingredient_factory_organic.h"

static struct pizza_dough *organic_create_dough(struct pizza_ingredient_factory *factory)
{
	static struct pizza_dough dough = {.ingredient = pizza_ingredient_organic };

	printf("ingredient_factory_organic::create_dough()\n");
	return &dough;
}

static struct pizza_sauce *organic_create_sauce(struct pizza_ingredient_factory *factory)
{
	static struct pizza_sauce sauce = {.ingredient = pizza_ingredient_organic };

	printf("ingredient_factory_organic::create_sauce()\n");
	return &sauce;
}

static struct pizza_ingredient_factory_ops ops = {
	.create_dough = organic_create_dough,
	.create_sauce = organic_create_sauce,
};

void pizza_ingredient_factory_organic_init(struct pizza_ingredient_factory_organic *factory)
{
	pizza_ingredient_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}
