
#include <stdlib.h> /* malloc */
#include <myobj.h>
#include "widget_motif_button.h"
#include "widget_motif_menu.h"
#include "widget_factory_motif.h"

static struct widget *motif_factory_create_button(struct widget_factory *factory)
{
	struct widget_motif_button *button;
	button = malloc(sizeof(*button));
	if (!button)
		return 0;
	widget_motif_button_init(button);
	return &button->widget;
}

static struct widget *motif_factory_create_menu(struct widget_factory *factory)
{
	struct widget_motif_menu *menu;
	menu = malloc(sizeof(*menu));
	if (!menu)
		return 0;
	widget_motif_menu_init(menu);
	return &menu->widget;
}

static struct widget_factory_ops ops = {
	.create_button = motif_factory_create_button,
	.create_menu = motif_factory_create_menu,
};

void widget_factory_motif_init(struct widget_factory_motif *factory)
{
	widget_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}
