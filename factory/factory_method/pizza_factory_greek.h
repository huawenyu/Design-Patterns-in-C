
#ifndef PIZZA_FACTORY_GREEK_H_
#define PIZZA_FACTORY_GREEK_H_

#include "pizza_factory.h"

struct pizza_factory_greek {
	struct pizza_factory factory;
};

void pizza_factory_greek_init(struct pizza_factory_greek *);

#endif /* PIZZA_FACTORY_GREEK_H_ */
