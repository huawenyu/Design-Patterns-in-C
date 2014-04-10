
#include <stdio.h>
#include <myobj.h>

#include "pizza_ingredient_factory_standard.h"

static struct pizza_dough *standard_create_dough(struct pizza_ingredient_factory *factory)
{
	printf("ingredient_factory_standard::create_dough()\n");
	return 0;
}

static struct pizza_sauce *standard_create_sauce(struct pizza_ingredient_factory *factory)
{
	printf("ingredient_factory_standard::create_sauce()\n");
	return 0;
}

static struct pizza_ingredient_factory_ops ops = {
	.create_dough = standard_create_dough,
	.create_sauce = standard_create_sauce,
};

void pizza_ingredient_factory_standard_init(struct pizza_ingredient_factory_standard *factory)
{
	pizza_ingredient_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}
