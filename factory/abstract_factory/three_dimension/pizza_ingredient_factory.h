
#ifndef PIZZA_INGREDIENT_FACTORY_H_
#define PIZZA_INGREDIENT_FACTORY_H_

#include "pizza.h"

struct pizza_ingredient_factory_ops;
struct pizza_ingredient_factory {
	struct pizza_ingredient_factory_ops *ops;
};

struct pizza_ingredient_factory_ops {
	struct pizza_dough *(*create_dough)(struct pizza_ingredient_factory *);
	struct pizza_sauce *(*create_sauce)(struct pizza_ingredient_factory *);
};

void pizza_ingredient_factory_init(struct pizza_ingredient_factory *);

static inline
struct pizza_dough *pizza_ingredient_factory_create_dough(struct pizza_ingredient_factory *factory)
{
	return factory->ops->create_dough(factory);
}

static inline
struct pizza_sauce *pizza_ingredient_factory_create_sauce(struct pizza_ingredient_factory *factory)
{
	return factory->ops->create_sauce(factory);
}

#endif /* PIZZA_INGREDIENT_FACTORY_H_ */
