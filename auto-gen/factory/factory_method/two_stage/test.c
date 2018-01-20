
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "product.h"
#include "factory_product.h"
#include "domain_class.h"
#include "serializer.h"
#include "file_access_handler.h"

static int test_two_stage(char *output, size_t sz)
{
	struct factory_product *factory;
	struct serializer *serializer;
	struct file_access_handler *file_handler;
	struct domain_class *dc;

	serializer = malloc(sizeof(*serializer)); // sanity check
	file_handler = malloc(sizeof(*file_handler)); // sanity check
	factory = malloc(sizeof(*factory)); // sanity check
	factory_product_init(factory, serializer, file_handler);

	dc = malloc(sizeof(*dc)); // sanity check
    product_do_something(factory_create(&factory->factory, dc));
	
	return 0;
}

void two_stage_test(void);
void two_stage_test(void)
{
	my_test_suite_add(test_two_stage, "Factory Method: two stage");
}
