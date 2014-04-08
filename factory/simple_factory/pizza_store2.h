
#ifndef PIZZA_STORE2_H_
#define PIZZA_STORE2_H_

#include "pizza.h"
#include "pizza_simple_factory.h"

struct pizza_store {
	struct pizza_simple_factory *factory;
};

void pizza_store_init(struct pizza_store *, struct pizza_simple_factory *);

/* static method */
struct pizza *pizza_store2_order_pizza(struct pizza_store *,
		const char *name, enum pizza_size_type);

#endif /* PIZZA_STORE2_H_ */
