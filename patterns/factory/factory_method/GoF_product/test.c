#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "concrete_product_1.h"
#include "concrete_product_2.h"
#include "product_factory_1.h"
#include "product_factory_2.h"

static int test_factory_method_gof(char *output, size_t sz)
{
	struct product *product;
	struct product_factory_1 *factory_1;
	struct product_factory_2 *factory_2;

	factory_1 = malloc(sizeof(*factory_1));
	product_factory_1_init(factory_1);

	factory_2 = malloc(sizeof(*factory_2));
	product_factory_2_init(factory_2);

	product = product_factory_create(&factory_1->product_factory);
	product_do_it(product, 2, 7);
	/* free product */

	product = product_factory_create(&factory_2->product_factory);
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
