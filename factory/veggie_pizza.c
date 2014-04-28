
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "veggie_pizza.h"


static void veggie_prepare(struct pizza *pizza)
{
	CLASS_SUPER(pizza, prepare);
	printf("veggie::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void veggie_bake(struct pizza *pizza)
{
	printf("veggie::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void veggie_cut(struct pizza *pizza)
{
	printf("veggie::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void veggie_box(struct pizza *pizza)
{
	printf("veggie::box(%s, %d)\n", pizza->name, pizza->size);
}

static void veggie_free(struct pizza *pizza)
{
	printf("veggie::free(%s, %d)\n", pizza->name, pizza->size);
	struct veggie_pizza *veggie = container_of(pizza, typeof(*veggie), pizza);
	free(veggie);
}

static struct pizza_ops veggie_ops = {
	.prepare = veggie_prepare,
	.bake = veggie_bake,
	.cut = veggie_cut,
	.box = veggie_box,
	.free = veggie_free,
};

void veggie_pizza_init(struct veggie_pizza *veggie, enum pizza_size_type type)
{
	pizza_init(&veggie->pizza);
	CLASS_OPS_INIT_WITH_SUPER(veggie->pizza.ops, veggie_ops, super);
	snprintf(veggie->pizza.name, sizeof(veggie->pizza.name), "veggie");
	veggie->pizza.size = type;
}
