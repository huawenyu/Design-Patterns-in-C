
#include <string.h> /* memset */
#include <stdio.h> /* printf */
#include <myobj.h>
#include "pizza.h"

static void pizza_ops_prepare(struct pizza *pizza)
{
	printf("pizza::prepare()\n");
	pizza->dough = (struct pizza_dough){.ingredient = pizza_ingredient_no_organic};
	pizza->sauce = (struct pizza_sauce){.ingredient = pizza_ingredient_no_organic};
}

static struct pizza_ops pizza_ops = { /* virtual method */
	.prepare = pizza_ops_prepare,
};

void pizza_init(struct pizza *pizza)
{
	pizza->ops = &pizza_ops;
	memset(pizza->name, 0, sizeof(pizza->name));
	pizza->size = pizza_size_normal;
	pizza->dough = (struct pizza_dough){.ingredient = pizza_ingredient_null};
	pizza->sauce = (struct pizza_sauce){.ingredient = pizza_ingredient_null};
}
