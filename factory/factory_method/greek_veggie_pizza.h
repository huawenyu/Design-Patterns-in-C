
#ifndef GREEK_VEGGIE_PIZZA_H_
#define GREEK_VEGGIE_PIZZA_H_

#include "pizza.h"

struct greek_veggie_pizza {
	struct pizza pizza;
};

void greek_veggie_pizza_init(struct greek_veggie_pizza *, enum pizza_size_type);

#endif /* GREEK_VEGGIE_PIZZA_H_ */
