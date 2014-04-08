
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "china_veggie_pizza.h"


static void china_veggie_prepare(struct pizza *pizza)
{
	printf("china_veggie::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void china_veggie_bake(struct pizza *pizza)
{
	printf("china_veggie::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void china_veggie_cut(struct pizza *pizza)
{
	printf("china_veggie::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void china_veggie_box(struct pizza *pizza)
{
	printf("china_veggie::box(%s, %d)\n", pizza->name, pizza->size);
}

static void china_veggie_free(struct pizza *pizza)
{
	printf("china_veggie::free(%s, %d)\n", pizza->name, pizza->size);
	struct china_veggie_pizza *china_veggie = container_of(pizza, typeof(*china_veggie), pizza);
	free(china_veggie);
}

static struct pizza_ops china_veggie_ops = {
	.prepare = china_veggie_prepare,
	.bake = china_veggie_bake,
	.cut = china_veggie_cut,
	.box = china_veggie_box,
	.free = china_veggie_free,
};

void china_veggie_pizza_init(struct china_veggie_pizza *china_veggie, enum pizza_size_type type)
{
	pizza_init(&china_veggie->pizza);
	CLASS_OPS_INIT(china_veggie->pizza.ops, china_veggie_ops);
	snprintf(china_veggie->pizza.name, sizeof(china_veggie->pizza.name), "china_veggie");
	china_veggie->pizza.size = type;
}
