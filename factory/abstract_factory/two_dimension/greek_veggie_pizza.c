
#include <stdlib.h> /* free */
#include <stdio.h> /* snprintf */
#include <myobj.h>
#include "greek_veggie_pizza.h"


static void greek_veggie_prepare(struct pizza *pizza)
{
	CLASS_SUPER(pizza, prepare);
	printf("greek_veggie::prepare(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_veggie_bake(struct pizza *pizza)
{
	printf("greek_veggie::bake(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_veggie_cut(struct pizza *pizza)
{
	printf("greek_veggie::cut(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_veggie_box(struct pizza *pizza)
{
	printf("greek_veggie::box(%s, %d)\n", pizza->name, pizza->size);
}

static void greek_veggie_free(struct pizza *pizza)
{
	printf("greek_veggie::free(%s, %d)\n", pizza->name, pizza->size);
	struct greek_veggie_pizza *greek_veggie = container_of(pizza, typeof(*greek_veggie), pizza);
	free(greek_veggie);
}

static struct pizza_ops greek_veggie_ops = {
	.prepare = greek_veggie_prepare,
	.bake = greek_veggie_bake,
	.cut = greek_veggie_cut,
	.box = greek_veggie_box,
	.free = greek_veggie_free,
};

void greek_veggie_pizza_init(struct greek_veggie_pizza *greek_veggie, enum pizza_size_type type)
{
	pizza_init(&greek_veggie->pizza);
	CLASS_OPS_INIT_WITH_SUPER(greek_veggie->pizza.ops, greek_veggie_ops, super);
	snprintf(greek_veggie->pizza.name, sizeof(greek_veggie->pizza.name), "greek_veggie");
	greek_veggie->pizza.size = type;
}
