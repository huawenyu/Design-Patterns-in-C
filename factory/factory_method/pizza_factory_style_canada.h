/* Normal style pizza */
#ifndef PIZZA_FACTORY_STYLE_CANADA_H_
#define PIZZA_FACTORY_STYLE_CANADA_H_

#include "pizza_factory.h"

struct pizza_factory_style_canada {
	struct pizza_factory factory;
};

void pizza_factory_style_canada_init(struct pizza_factory_style_canada *);

#endif /* PIZZA_FACTORY_H_ */
