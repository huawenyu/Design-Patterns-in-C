
#ifndef WIDGET_WINDOWS_FACTORY_H_
#define WIDGET_WINDOWS_FACTORY_H_

#include "widget_factory.h"

struct widget_windows_factory {
	struct widget_factory factory;
};

void widget_windows_factory_init(struct widget_windows_factory *);

#endif /* WIDGET_WINDOWS_FACTORY_H_ */
