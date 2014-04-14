
#include <stdio.h>
#include <myobj.h>
#include "child.h"

static void child_v_override_who(struct parent *parent)
{
	printf("[virtual-override] I'm %s.\n", parent->name);
}

static struct parent_ops parent_ops = {
	.v_override_who = child_v_override_who,
};

static void v_child_right(struct child *child, const char *myright)
{
	printf("[virtual of child] I'm %s, so I can %s\n", child->parent.name, myright);
}

static struct child_ops ops = {
	.v_child_right = v_child_right,
};

void child_init(struct child *child)
{
	parent_init(&child->parent);
	CLASS_OPS_INIT(child->parent.ops, parent_ops);
	child->ops = &ops;
	snprintf(child->parent.name, sizeof(child->parent.name), "Child-Tom");
}
