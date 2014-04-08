
#include <string.h>
#include "pizza_factory.h"

static struct pizza_factory_ops ops = {0}; /* virtual */

void pizza_factory_init(struct pizza_factory *factory)
{
	factory->ops = &ops;
}

