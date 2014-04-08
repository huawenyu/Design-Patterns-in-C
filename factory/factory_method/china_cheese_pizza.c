
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "china_cheese_pizza.h"

static void china_cheese_prepare(struct pizza *pizza)
{
	printf("china_cheese::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void china_cheese_bake(struct pizza *pizza)
{
	printf("china_cheese::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void china_cheese_cut(struct pizza *pizza)
{
	printf("china_cheese::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void china_cheese_box(struct pizza *pizza)
{
	printf("china_cheese::box(%s, %d)\n", pizza->name, pizza->size);
}

static void china_cheese_free(struct pizza *pizza)
{
	printf("china_cheese::free(%s, %d)\n", pizza->name, pizza->size);
	struct china_cheese_pizza *china_cheese = container_of(pizza, typeof(*china_cheese), pizza);
	free(china_cheese);
}

static struct pizza_ops china_cheese_ops = {
	.prepare = china_cheese_prepare,
	.bake = china_cheese_bake,
	.cut = china_cheese_cut,
	.box = china_cheese_box,
	.free = china_cheese_free,
};

void china_cheese_pizza_init(struct china_cheese_pizza *china_cheese, enum pizza_size_type type)
{
	pizza_init(&china_cheese->pizza);
	CLASS_OPS_INIT(china_cheese->pizza.ops, china_cheese_ops);
	snprintf(china_cheese->pizza.name, sizeof(china_cheese->pizza.name), "china_cheese");
	china_cheese->pizza.size = type;
}
