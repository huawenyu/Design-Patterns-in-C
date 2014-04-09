
#include <stdio.h>
#include <myobj.h>
#include "widget_motif_button.h"

static void motif_button_draw(struct widget *widget)
{
	printf("motif::button.draw()\n");
}

static struct widget_ops ops = {
	.draw = motif_button_draw,
};

void widget_motif_button_init(struct widget_motif_button *widget)
{
	widget_init(&widget->widget);
	CLASS_OPS_INIT(widget->widget.ops, ops);
}
