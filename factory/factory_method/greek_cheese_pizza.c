
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "greek_cheese_pizza.h"

static void greek_cheese_prepare(struct pizza *pizza)
{
	printf("greek_cheese::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_cheese_bake(struct pizza *pizza)
{
	printf("greek_cheese::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_cheese_cut(struct pizza *pizza)
{
	printf("greek_cheese::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_cheese_box(struct pizza *pizza)
{
	printf("greek_cheese::box(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_cheese_free(struct pizza *pizza)
{
	printf("greek_cheese::free(%s, %d)\n", pizza->name, pizza->size);
	struct greek_cheese_pizza *greek_cheese = container_of(pizza, typeof(*greek_cheese), pizza);
	free(greek_cheese);
}

static struct pizza_ops greek_cheese_ops = {
	.prepare = greek_cheese_prepare,
	.bake = greek_cheese_bake,
	.cut = greek_cheese_cut,
	.box = greek_cheese_box,
	.free = greek_cheese_free,
};

void greek_cheese_pizza_init(struct greek_cheese_pizza *greek_cheese, enum pizza_size_type type)
{
	pizza_init(&greek_cheese->pizza);
	CLASS_OPS_INIT(greek_cheese->pizza.ops, greek_cheese_ops);
	snprintf(greek_cheese->pizza.name, sizeof(greek_cheese->pizza.name), "greek_cheese");
	greek_cheese->pizza.size = type;
}
