
#ifndef WIDGET_FACTORY_H_
#define WIDGET_FACTORY_H_

#include "widget.h"

struct widget_factory_ops;
struct widget_factory {
	struct widget_factory_ops *ops;
};

struct widget_factory_ops {
	struct widget *(*create_button)(struct widget_factory *);
	struct widget *(*create_menu)(struct widget_factory *);
};

void widget_factory_init(struct widget_factory *);

static inline
struct widget *widget_factory_create_button(struct widget_factory *factory)
{
	return factory->ops->create_button(factory);
}

static inline
struct widget *widget_factory_create_menu(struct widget_factory *factory)
{
	return factory->ops->create_menu(factory);
}

#endif /* WIDGET_FACTORY_H_ */
