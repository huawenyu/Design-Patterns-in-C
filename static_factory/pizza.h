
#ifndef PIZZA_H_
#define PIZZA_H_

enum pizza_size_type {
	pizza_size_small,
	pizza_size_normal,
	pizza_size_large,
};

struct pizza_ops;
struct pizza {
	char name[32];
	enum pizza_size_type size;
	struct pizza_ops *ops;
};

struct pizza_ops {
	void (*prepare)(struct pizza *);
	void (*bake)(struct pizza *);
	void (*cut)(struct pizza *);
	void (*box)(struct pizza *);
	void (*free)(struct pizza *);
};

void pizza_init(struct pizza *);

static inline
pizza_prepare(struct pizza *pizza)
{
	pizza->ops->prepare(pizza);
}

static inline
pizza_bake(struct pizza *pizza)
{
	pizza->ops->bake(pizza);
}

static inline
pizza_cut(struct pizza *pizza)
{
	pizza->ops->cut(pizza);
}

static inline
pizza_box(struct pizza *pizza)
{
	pizza->ops->box(pizza);
}

static inline
pizza_free(struct pizza *pizza)
{
	pizza->ops->free(pizza);
}

#endif /* PIZZA_H_ */
