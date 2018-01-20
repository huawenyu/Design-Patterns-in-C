
#ifndef WIDGET_H_
#define WIDGET_H_

struct widget_ops;
struct widget {
	struct widget_ops *ops;
};

struct widget_ops {
	void (*draw)(struct widget *);
};

void widget_init(struct widget *);

static inline
void widget_draw(struct widget *widget)
{
	widget->ops->draw(widget);
}

#endif /* WIDGET_H_ */
