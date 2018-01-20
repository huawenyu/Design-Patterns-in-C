
#ifndef __FACTORY_H__
#define __FACTORY_H__


struct factory_ops;
struct factory {
	struct factory_ops *ops;
};
struct factory_ops {
	struct product * (*create)(struct factory *);
};
void factory_init(struct factory *);

void factory_do_it(struct factory *);

static inline struct product * factory_create(struct factory *factory)
{
	return factory->ops->create(factory);
}

#endif /* __FACTORY_H__ */
