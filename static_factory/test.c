
#include <stdio.h>
#include <stdlib.h>
#include "product.h"

static int test(void)
{
	struct product *product;
	product = create_product(product_one);
	product_do_it(product);
	free(product);

	product = create_product(product_two);
	product_do_it(product);
	free(product);

	return 0;
}

void static_factory_test()
{
	my_test_suite_add(test, "static factory test");
}
