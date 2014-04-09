
#include <stdio.h> /* printf */
#include <myobj.h>
#include "widget_windows_button.h"

static void windows_button_draw(struct widget *widget)
{
	printf("windows::button.draw()\n");
}

static struct widget_ops ops = {
	.draw = windows_button_draw,
};

void widget_windows_button_init(struct widget_windows_button *widget)
{
	widget_init(&widget->widget);
	CLASS_OPS_INIT(widget->widget.ops, ops);
}
