
#ifndef WIDGET_FACTORY_MOTIF_H_
#define WIDGET_FACTORY_MOTIF_H_

#include "widget_factory.h"

struct widget_factory_motif {
	struct widget_factory factory;
};

void widget_factory_motif_init(struct widget_factory_motif *);

#endif /* WIDGET_FACTORY_MOTIF_H_ */
