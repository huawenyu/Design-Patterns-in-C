
#include <string.h> /* memset */
#include "pizza.h"

static struct pizza_ops pizza_ops = {0}; /* virtual method */

void pizza_init(struct pizza *pizza)
{
	pizza->ops = &pizza_ops;
	memset(pizza->name, 0, sizeof(pizza->name));
	pizza->size = pizza_size_normal;
}
