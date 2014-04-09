
#ifndef WIDGET_MOTIF_BUTTON_H_
#define WIDGET_MOTIF_BUTTON_H_

#include "widget.h"

struct widget_motif_button {
	struct widget widget;
};

void widget_motif_button_init(struct widget_motif_button *);

#endif /* WIDGET_MOTIF_BUTTON_H_ */
