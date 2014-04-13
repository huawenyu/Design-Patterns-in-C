
#ifndef PIZZA_INGREDIENT_FACTORY_ORGANIC_H_
#define PIZZA_INGREDIENT_FACTORY_ORGANIC_H_

#include "pizza_ingredient_factory.h"

struct pizza_ingredient_factory_organic {
	struct pizza_ingredient_factory factory;
};

void pizza_ingredient_factory_organic_init(struct pizza_ingredient_factory_organic *);

#endif /* PIZZA_INGREDIENT_FACTORY_ORGANIC_H_ */
