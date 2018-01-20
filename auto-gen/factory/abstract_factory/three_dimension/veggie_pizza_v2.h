
#ifndef VEGGIE_PIZZA_V2_H_
#define VEGGIE_PIZZA_V2_H_

#include "../../veggie_pizza.h"
#include "pizza_ingredient_factory.h"

struct veggie_pizza_v2 {
	struct veggie_pizza pizza;
	struct pizza_ingredient_factory *factory;
};

void veggie_pizza_v2_init(struct veggie_pizza_v2 *, enum pizza_size_type type,
		struct pizza_ingredient_factory *);

#endif /* VEGGIE_PIZZA_V2_H_ */
