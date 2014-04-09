
#ifndef WIDGET_MOTIF_FACTORY_H_
#define WIDGET_MOTIF_FACTORY_H_

#include "widget_factory.h"

struct widget_motif_factory {
	struct widget_factory factory;
};

void widget_motif_factory_init(struct widget_motif_factory *);

#endif /* WIDGET_MOTIF_FACTORY_H_ */
