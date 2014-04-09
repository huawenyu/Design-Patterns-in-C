
#include "widget_factory.h"

static struct widget_factory_ops ops = {0}; /* virtual */

void widget_factory_init(struct widget_factory *factory)
{
	factory->ops = &ops;
}
