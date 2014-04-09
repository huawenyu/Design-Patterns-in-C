
#include <stdlib.h> /* malloc */
#include <myobj.h>

#include "widget_windows_button.h"
#include "widget_windows_menu.h"
#include "widget_windows_factory.h"

static struct widget *windows_factory_create_button(struct widget_factory *factory)
{
	struct widget_windows_button *button;
	button = malloc(sizeof(*button));
	if (!button)
		return 0;
	widget_windows_button_init(button);
	return &button->widget;
}

static struct widget *windows_factory_create_menu(struct widget_factory *factory)
{
	struct widget_windows_menu *menu;
	menu = malloc(sizeof(*menu));
	if (!menu)
		return 0;
	widget_windows_menu_init(menu);
	return &menu->widget;
}

static struct widget_factory_ops ops = {
	.create_button = windows_factory_create_button,
	.create_menu = windows_factory_create_menu,
};

void widget_windows_factory_init(struct widget_windows_factory *factory)
{
	widget_factory_init(&factory->factory);
	CLASS_OPS_INIT(factory->factory.ops, ops);
}
