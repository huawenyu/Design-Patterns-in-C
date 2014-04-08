
#ifndef PIZZA_STORE2_H_
#define PIZZA_STORE2_H_

#include "pizza.h"
#include "pizza_simple_factory.h"

struct pizza_store2 {
	struct pizza_simple_factory *factory;
};

/* static method */
void pizza_store2_init(struct pizza_store2 *, struct pizza_simple_factory *);
void pizza_store2_free(struct pizza_store2 *);
struct pizza *pizza_store2_order_pizza(struct pizza_store2 *,
		const char *name, enum pizza_size_type);

#endif /* PIZZA_STORE2_H_ */
