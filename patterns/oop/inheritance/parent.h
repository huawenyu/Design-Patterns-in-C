
#ifndef PARENT_H_
#define PARENT_H_

struct parent_ops;
struct parent {
	struct parent_ops *ops;
	char name[32];
};

struct parent_ops {
	void (*v_override_who)(struct parent *);
	void (*v_ancestor)(struct parent *);
};

void parent_init(struct parent *);
void parent_method_work(struct parent *);

static inline
void parent_v_override_who(struct parent *parent)
{
	parent->ops->v_override_who(parent);
}

static inline
void parent_v_ancestor(struct parent *parent)
{
	parent->ops->v_ancestor(parent);
}

#endif /* PARENT_H_ */
