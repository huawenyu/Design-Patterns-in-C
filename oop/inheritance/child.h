
#ifndef CHILD_H_
#define CHILD_H_

#include "parent.h"

struct child_ops;
struct child {
	struct parent parent;
	struct child_ops *ops;
};

struct child_ops {
	void (*v_child_right)(struct child *, const char *);
};

void child_init(struct child *);

static inline
void child_v_child_right(struct child *child, const char *myright)
{
	child->ops->v_child_right(child, myright);
}

#endif /* CHILD_H_ */
