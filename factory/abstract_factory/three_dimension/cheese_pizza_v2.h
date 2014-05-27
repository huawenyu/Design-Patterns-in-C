
#ifndef CHEESE_PIZZA_V2_H_
#define CHEESE_PIZZA_V2_H_

#include "../../cheese_pizza.h"
#include "pizza_ingredient_factory.h"

struct cheese_pizza_v2 {
	struct cheese_pizza pizza;
	struct pizza_ingredient_factory *factory;
};

void cheese_pizza_v2_init(struct cheese_pizza_v2 *, enum pizza_size_type type,
		struct pizza_ingredient_factory *);

#endif /* CHEESE_PIZZA_V2_H_ */
