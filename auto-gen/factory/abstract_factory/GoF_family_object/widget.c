
#include "widget.h"

static struct widget_ops ops = {0}; /* virtual */

void widget_init(struct widget *widget)
{
	widget->ops = &ops;
}
