
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "product.h"


static void product_ops_do_it(struct product *product, int a, int b)
{
	printf("product::do_it()\n");
}
static struct product_ops product_ops = {
	.do_it = product_ops_do_it,
};

void product_init(struct product *product)
{
	memset(product, sizeof(*product), 0);
	product->ops = &product_ops;
}

