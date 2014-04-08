
#ifndef CHINA_CHEESE_PIZZA_H_
#define CHINA_CHEESE_PIZZA_H_

#include "pizza.h"

struct china_cheese_pizza {
	struct pizza pizza;
};

void china_cheese_pizza_init(struct china_cheese_pizza *, enum pizza_size_type);

#endif /* CHINA_CHEESE_PIZZA_H_ */
