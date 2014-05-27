
#ifndef PIZZA_FACTORY_H_
#define PIZZA_FACTORY_H_

#include "../../pizza.h"

struct pizza_factory_ops;
struct pizza_factory { /* interface */
	struct pizza_factory_ops *ops;
};

struct pizza_factory_ops {
	/* virtual | private, implement by sub-class */
	struct pizza *(*create)(struct pizza_factory *, const char *name, enum pizza_size_type size);
	void (*free)(struct pizza_factory *);
};

static inline
struct pizza *pizza_factory_create(struct pizza_factory *factory,
		const char *name, enum pizza_size_type size)
{
	return factory->ops->create(factory, name, size);
}

static inline
void pizza_factory_free(struct pizza_factory *factory)
{
	factory->ops->free(factory);
}

void pizza_factory_init(struct pizza_factory *);

#endif /* PIZZA_FACTORY_H_ */
