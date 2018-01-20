
#ifndef VEGGIE_PIZZA_H_
#define VEGGIE_PIZZA_H_

#include "pizza.h"

struct veggie_pizza {
	struct pizza pizza;
};

void veggie_pizza_init(struct veggie_pizza *, enum pizza_size_type);

#endif /* VEGGIE_PIZZA_H_ */
