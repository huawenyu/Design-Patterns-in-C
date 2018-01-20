
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "factory.h"


static struct product * factory_ops_create(struct factory *factory)
{
	printf("factory::create()\n");
	return 0;
}
static struct factory_ops factory_ops = {
	.create = factory_ops_create,
};

void factory_init(struct factory *factory)
{
	memset(factory, sizeof(*factory), 0);
	factory->ops = &factory_ops;
}


void factory_do_it(struct factory *factory)
{
	printf("factory::do_it()\n");
}