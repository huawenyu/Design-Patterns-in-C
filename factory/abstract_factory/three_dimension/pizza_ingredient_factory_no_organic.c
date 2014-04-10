
#include <stdio.h>
#include <myobj.h>

#include "pizza_ingredient_factory_no_organic.h"

static struct pizza_dough *no_organic_create_dough(struct pizza_ingredient_factory *factory)
{
	static struct pizza_dough dough = {.ingredient = pizza_ingredient_no_organic };

	printf("ingredient_factory_no_organic::create_dough()\n");
	return &dough;
}

static struct pizza_sauce *no_organic_create_sauce(struct pizza_ingredient_factory *factory)
{
	static struct pizza_sauce sauce = {.ingredient = pizza_ingredient_no_organic };

	printf("ingredient_factory_no_organic::create_sauce()\n");
	return &sauce;
}

static struct pizza_ingredient_factory_ops ops = {
	.create_dough = no_organic_create_dough,
	.create_sauce = no_organic_create_sauce,
};

void pizza_ingredient_factory_no_organic_init(struct pizza_ingredient_factory_no_organic *factory)
{
	pizza_ingredient_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}
