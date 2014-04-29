
/**
 * factory_product.c  2014-04-29 17:03:57
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <myobj.h>
#include "factory_product.h"


static struct product * factory_product_ops_create(struct factory *factory, struct domain_class *dc)
{
	printf("factory_product::create()\n");
	return 0;
}

static struct factory_ops factory_ops = {
	.create = factory_product_ops_create,
};


void factory_product_init(struct factory_product *factory_product, struct serializer *s, struct file_access_handler *f)
{
	memset(factory_product, sizeof(*factory_product), 0);
	factory_init(&factory_product->factory);
	CLASS_OPS_INIT(factory_product->factory.ops, factory_ops);
	factory_product->serializer = s;
	factory_product->file_access_handler = f;
}

