#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "concrete_product_1.h"
#include "concrete_product_2.h"
#include "factory_product_1.h"
#include "factory_product_2.h"

static int test_factory_method_gof(char *output, size_t sz)
{
	struct product *product;
	struct factory_product_1 *factory_1;
	struct factory_product_2 *factory_2;

	factory_1 = malloc(sizeof(*factory_1));
	factory_product_1_init(factory_1);

	factory_2 = malloc(sizeof(*factory_2));
	factory_product_2_init(factory_2);

	product = factory_create(&factory_1->factory);
	product_do_it(product, 2, 7);
	/* free product */

	product = factory_create(&factory_2->factory);
	product_do_it(product, 3, 10);
	/* free product */

	/* free two factory */

	return 0;
}

void factory_method_gof_test(void);
void factory_method_gof_test(void)
{
	my_test_suite_add(test_factory_method_gof, "Factory Method GoF-Product");
}
