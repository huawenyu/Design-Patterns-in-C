
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "concrete_product_1.h"


static void concrete_product_1_ops_do_it(struct product *product, int a, int b)
{
	printf("concrete_product_1::do_it()\n");
}

static struct product_ops product_ops = {
	.do_it = concrete_product_1_ops_do_it,
};


void concrete_product_1_init(struct concrete_product_1 *concrete_product_1)
{
	memset(concrete_product_1, sizeof(*concrete_product_1), 0);
	product_init(&concrete_product_1->product);
	CLASS_OPS_INIT(concrete_product_1->product.ops, product_ops);
}

