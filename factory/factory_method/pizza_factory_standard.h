/* Normal style pizza */
#ifndef PIZZA_FACTORY_STANDARD_H_
#define PIZZA_FACTORY_STANDARD_H_

#include "pizza_factory.h"

struct pizza_factory_standard {
	struct pizza_factory factory;
};

void pizza_factory_standard_init(struct pizza_factory_standard *);

#endif /* PIZZA_FACTORY_STANDARD_H_ */
