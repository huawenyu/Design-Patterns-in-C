
#include "pizza_ingredient_factory.h"

static struct pizza_ingredient_factory_ops ops = {0}; /* virtual */

void pizza_ingredient_factory_init(struct pizza_ingredient_factory *factory)
{
	factory->ops = &ops;
}
