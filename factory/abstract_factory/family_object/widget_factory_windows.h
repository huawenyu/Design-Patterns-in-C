
#ifndef WIDGET_FACTORY_WINDOWS_H_
#define WIDGET_FACTORY_WINDOWS_H_

#include "widget_factory.h"

struct widget_factory_windows {
	struct widget_factory factory;
};

void widget_factory_windows_init(struct widget_factory_windows *);

#endif /* WIDGET_FACTORY_WINDOWS_H_ */
