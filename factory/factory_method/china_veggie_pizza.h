
#ifndef CHINA_VEGGIE_PIZZA_H_
#define CHINA_VEGGIE_PIZZA_H_

#include "pizza.h"

struct china_veggie_pizza {
	struct pizza pizza;
};

void china_veggie_pizza_init(struct china_veggie_pizza *, enum pizza_size_type);

#endif /* CHINA_VEGGIE_PIZZA_H_ */
