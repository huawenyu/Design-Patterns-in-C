/**Simple Factory
   Encapsulate the create method into class,
     let the store just depend on this factory.
 */
#ifndef PIZZA_SIMPLE_FACTORY_H_
#define PIZZA_SIMPLE_FACTORY_H_

#include "pizza.h"

struct pizza_simple_factory_ops;
struct pizza_simple_factory {
	struct pizza_simple_factory_ops *ops;
};

struct pizza_simple_factory_ops {
	struct pizza *(*create)(const char *name, enum pizza_size_type size);
};

static inline
struct pizza *pizza_simple_factory_create(struct pizza_simple_factory *factory,
		const char *name, enum pizza_size_type size)
{
	return factory->ops->create(name, size);
}

void pizza_simple_factory_init(struct pizza_simple_factory *);

#endif /* PIZZA_SIMPLE_FACTORY_H_ */
