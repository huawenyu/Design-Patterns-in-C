/* Normal style pizza */
#ifndef PIZZA_FACTORY_STANDARD_V2_H_
#define PIZZA_FACTORY_STANDARD_V2_H_

#include "pizza_factory.h"
#include "pizza_ingredient_factory.h"

struct pizza_factory_standard_v2 {
	struct pizza_factory factory;
	struct pizza_ingredient_factory *ingredient_factory;
};

void pizza_factory_standard_v2_init(struct pizza_factory_standard_v2 *,
		struct pizza_ingredient_factory *);

#endif /* PIZZA_FACTORY_STANDARD_V2_H_ */
