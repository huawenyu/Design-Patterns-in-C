
#include <stdio.h> /* printf */
#include <myobj.h>
#include "widget_windows_menu.h"

static void windows_menu_draw(struct widget *widget)
{
	printf("windows::menu.draw()\n");
}

static struct widget_ops ops = {
	.draw = windows_menu_draw,
};

void widget_windows_menu_init(struct widget_windows_menu *widget)
{
	widget_init(&widget->widget);
	CLASS_OPS_INIT(widget->widget.ops, ops);
}
