/**PizzaStore3
   Depend on the interface|abstract pizza_factory,
     the implement of how to CreatePizza delay to Sub-Class
 */
#ifndef PIZZA_STORE3_H_
#define PIZZA_STORE3_H_

#include "pizza.h"
#include "pizza_factory.h"

struct pizza_store3 {
	struct pizza_factory *factory;
};

void pizza_store3_init(struct pizza_store3 *);
void pizza_store3_free(struct pizza_store3 *);
void pizza_store3_set_factory(struct pizza_store3 *, struct pizza_factory *);

/* static method */
struct pizza *pizza_store3_order_pizza(struct pizza_store3 *,
		const char *name, enum pizza_size_type);

#endif /* PIZZA_STORE3_H_ */
