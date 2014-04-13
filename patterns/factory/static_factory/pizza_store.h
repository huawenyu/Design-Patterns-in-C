
#ifndef PIZZA_STORE_H_
#define PIZZA_STORE_H_

#include "pizza.h"

struct pizza *pizza_store_create_pizza(const char *name, enum pizza_size_type);
struct pizza *pizza_store_order_pizza(const char *name, enum pizza_size_type);

#endif /* PIZZA_STORE_H_ */
