
#include <stdio.h>
#include <myobj.h>
#include "widget_motif_menu.h"

static void motif_menu_draw(struct widget *widget)
{
	printf("motif::menu.draw()\n");
}

static struct widget_ops ops = {
	.draw = motif_menu_draw,
};

void widget_motif_menu_init(struct widget_motif_menu *widget)
{
	widget_init(&widget->widget);
	CLASS_OPS_INIT(widget->widget.ops, ops);
}
