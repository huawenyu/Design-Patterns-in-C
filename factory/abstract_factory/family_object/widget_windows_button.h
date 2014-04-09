
#ifndef WIDGET_WINDOWS_BUTTON_H_
#define WIDGET_WINDOWS_BUTTON_H_

#include "widget.h"

struct widget_windows_button {
	struct widget widget;
};

void widget_windows_button_init(struct widget_windows_button *);

#endif /* WIDGET_WINDOWS_BUTTON_H_ */
