
#include <string.h>
#include <stdlib.h>
#include "pizza_store.h"
#include "cheese_pizza.h"
#include "veggie_pizza.h"

/* static factory: extract from order_pizza */
struct pizza *pizza_store_create_pizza(const char *name, enum pizza_size_type size)
{
	struct pizza *pizza = 0;
	struct cheese_pizza *cheese;
	struct veggie_pizza *veggie;

	if (!strcmp(name, "cheese")) {
		cheese = malloc(sizeof(*cheese));
		if (!cheese)
			return 0;

		cheese_pizza_init(cheese, size);
		pizza = &cheese->pizza;
	}
	else if (!strcmp(name, "veggie")) {
		veggie = malloc(sizeof(*veggie));
		if (!veggie)
			return 0;

		veggie_pizza_init(veggie, size);
		pizza = &veggie->pizza;
	}
	return pizza;
}

struct pizza *pizza_store_order_pizza(const char *name, enum pizza_size_type size)
{
	struct pizza *pizza;
	pizza = pizza_store_create_pizza(name, size);
	if (!pizza)
		return 0;

	pizza_prepare(pizza);
	pizza_bake(pizza);
	pizza_cut(pizza);
	pizza_box(pizza);

	return pizza;
}
