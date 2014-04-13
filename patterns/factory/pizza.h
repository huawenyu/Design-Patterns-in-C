
#ifndef PIZZA_H_
#define PIZZA_H_

enum pizza_size_type {
	pizza_size_small,
	pizza_size_normal,
	pizza_size_large,
};

enum pizza_ingredient_type {
	pizza_ingredient_null,
	pizza_ingredient_no_organic,
	pizza_ingredient_organic,
};

/* support organic */
struct pizza_dough {
	enum pizza_ingredient_type ingredient;
};

struct pizza_sauce {
	enum pizza_ingredient_type ingredient;
};

struct pizza_ops;
struct pizza {
	char name[32];
	enum pizza_size_type size;
	struct pizza_ops *ops;

	struct pizza_dough dough;
	struct pizza_sauce sauce;
	/* Also we can organic ingredient cheese,veggie */
};

struct pizza_ops {
	void (*prepare)(struct pizza *);
	void (*bake)(struct pizza *);
	void (*cut)(struct pizza *);
	void (*box)(struct pizza *);
	void (*free)(struct pizza *);

	struct pizza_ops *super;
};

void pizza_init(struct pizza *);

static inline
void pizza_prepare(struct pizza *pizza)
{
	pizza->ops->prepare(pizza);
}

static inline
void pizza_bake(struct pizza *pizza)
{
	pizza->ops->bake(pizza);
}

static inline
void pizza_cut(struct pizza *pizza)
{
	pizza->ops->cut(pizza);
}

static inline
void pizza_box(struct pizza *pizza)
{
	pizza->ops->box(pizza);
}

static inline
void pizza_free(struct pizza *pizza)
{
	pizza->ops->free(pizza);
}

#endif /* PIZZA_H_ */
