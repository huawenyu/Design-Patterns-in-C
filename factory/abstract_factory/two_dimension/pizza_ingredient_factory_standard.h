
#ifndef PIZZA_INGREDIENT_FACTORY_STANDARD_H_
#define PIZZA_INGREDIENT_FACTORY_STANDARD_H_

#include "pizza_ingredient_factory.h"

struct pizza_ingredient_factory_standard {
	struct pizza_ingredient_factory factory;
};

void pizza_ingredient_factory_standard_init(struct pizza_ingredient_factory_standard *);

#endif /* PIZZA_INGREDIENT_FACTORY_STANDARD_H_ */
