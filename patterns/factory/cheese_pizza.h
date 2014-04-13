
#ifndef CHEESE_PIZZA_H_
#define CHEESE_PIZZA_H_

#include "pizza.h"

struct cheese_pizza {
	struct pizza pizza;
};

void cheese_pizza_init(struct cheese_pizza *, enum pizza_size_type);

#endif /* CHEESE_PIZZA_H_ */
