
#include <stdio.h>
#include <myobj.h>
#include "pizza_ingredient_factory.h"
#include "veggie_pizza_v2.h"

static void veggie_v2_prepare(struct pizza *pizza)
{
	struct veggie_pizza_v2 *veggie = container_of(pizza, typeof(*veggie), pizza.pizza);

	CLASS_SUPER(pizza, prepare);

	pizza->dough = *pizza_ingredient_factory_create_dough(veggie->factory);
	pizza->sauce = *pizza_ingredient_factory_create_sauce(veggie->factory);
	printf("veggie_pizza_v2::prepare()\n");
}

static struct pizza_ops ops = {
	.prepare = veggie_v2_prepare,
};

void veggie_pizza_v2_init(struct veggie_pizza_v2 *pizza, enum pizza_size_type type,
		struct pizza_ingredient_factory *factory)
{
	veggie_pizza_init(&pizza->pizza, type);
	CLASS_OPS_INIT_WITH_SUPER(pizza->pizza.pizza.ops, ops, super);
	pizza->factory = factory;
}
