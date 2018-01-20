
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "concrete_product_2.h"


static void concrete_product_2_ops_do_it(struct product *product, int a, int b)
{
	printf("concrete_product_2::do_it()\n");
}

static struct product_ops product_ops = {
	.do_it = concrete_product_2_ops_do_it,
};


void concrete_product_2_init(struct concrete_product_2 *concrete_product_2)
{
	memset(concrete_product_2, sizeof(*concrete_product_2), 0);
	product_init(&concrete_product_2->product);
	CLASS_OPS_INIT(concrete_product_2->product.ops, product_ops);
}

