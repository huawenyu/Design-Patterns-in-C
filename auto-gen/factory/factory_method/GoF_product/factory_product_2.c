
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "concrete_product_2.h"
#include "factory_product_2.h"


static struct product * factory_product_2_ops_create(struct factory *factory)
{
	struct concrete_product_2 *p2;

	printf("factory_product_2::create()\n");
	p2 = malloc(sizeof(*p2));
	concrete_product_2_init(p2);
	return &p2->product;
}

static struct factory_ops factory_ops = {
	.create = factory_product_2_ops_create,
};


void factory_product_2_init(struct factory_product_2 *factory_product_2)
{
	memset(factory_product_2, sizeof(*factory_product_2), 0);
	factory_init(&factory_product_2->factory);
	CLASS_OPS_INIT(factory_product_2->factory.ops, factory_ops);
}

