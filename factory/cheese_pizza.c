
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "cheese_pizza.h"

static void cheese_prepare(struct pizza *pizza)
{
	printf("cheese::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void cheese_bake(struct pizza *pizza)
{
	printf("cheese::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void cheese_cut(struct pizza *pizza)
{
	printf("cheese::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void cheese_box(struct pizza *pizza)
{
	printf("cheese::box(%s, %d)\n", pizza->name, pizza->size);
}

static void cheese_free(struct pizza *pizza)
{
	printf("cheese::free(%s, %d)\n", pizza->name, pizza->size);
	struct cheese_pizza *cheese = container_of(pizza, typeof(*cheese), pizza);
	free(cheese);
}

static struct pizza_ops cheese_ops = {
	.prepare = cheese_prepare,
	.bake = cheese_bake,
	.cut = cheese_cut,
	.box = cheese_box,
	.free = cheese_free,
};

void cheese_pizza_init(struct cheese_pizza *cheese, enum pizza_size_type type)
{
	pizza_init(&cheese->pizza);
	CLASS_OPS_INIT(cheese->pizza.ops, cheese_ops);
	snprintf(cheese->pizza.name, sizeof(cheese->pizza.name), "cheese");
	cheese->pizza.size = type;
}
