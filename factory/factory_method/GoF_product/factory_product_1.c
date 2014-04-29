
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "concrete_product_1.h"
#include "factory_product_1.h"


static struct product * factory_product_1_ops_create(struct factory *factory)
{
	struct concrete_product_1 *p1;

	printf("factory_product_1::create()\n");
	p1 = malloc(sizeof(*p1));
	concrete_product_1_init(p1);
	return &p1->product;
}

static struct factory_ops factory_ops = {
	.create = factory_product_1_ops_create,
};


void factory_product_1_init(struct factory_product_1 *factory_product_1)
{
	memset(factory_product_1, sizeof(*factory_product_1), 0);
	factory_init(&factory_product_1->factory);
	CLASS_OPS_INIT(factory_product_1->factory.ops, factory_ops);
}

