
#ifndef GREEK_CHEESE_PIZZA_H_
#define GREEK_CHEESE_PIZZA_H_

#include "pizza.h"

struct greek_cheese_pizza {
	struct pizza pizza;
};

void greek_cheese_pizza_init(struct greek_cheese_pizza *, enum pizza_size_type);

#endif /* GREEK_CHEESE_PIZZA_H_ */
