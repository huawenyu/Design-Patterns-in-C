
#include <stdio.h>
#include <myobj.h>
#include "pizza_ingredient_factory.h"
#include "cheese_pizza_v2.h"

static void cheese_v2_prepare(struct pizza *pizza)
{
	struct cheese_pizza_v2 *cheese = container_of(pizza, typeof(*cheese), pizza.pizza);

	CLASS_SUPER(pizza, prepare);

	pizza->dough = *pizza_ingredient_factory_create_dough(cheese->factory);
	pizza->sauce = *pizza_ingredient_factory_create_sauce(cheese->factory);
	printf("cheese_pizza_v2::prepare()\n");
}

static struct pizza_ops cheese_v2_ops = {
	.prepare = cheese_v2_prepare,
};

void cheese_pizza_v2_init(struct cheese_pizza_v2 *pizza, enum pizza_size_type type,
		struct pizza_ingredient_factory *factory)
{
	cheese_pizza_init(&pizza->pizza, type);
	CLASS_OPS_INIT_SUPER(pizza->pizza.pizza.ops, cheese_v2_ops);
	pizza->factory = factory;
}
