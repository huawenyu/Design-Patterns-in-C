
#include <stdio.h>
#include "parent.h"

static void v_override_who(struct parent *parent)
{
	printf("[virtual-override] I'm %s.\n", parent->name);
}

static void v_ancestor(struct parent *parent)
{
	printf("[virtual-no-override] We all have same Ancestor.\n");
}

static struct parent_ops ops = {
	.v_override_who = v_override_who,
	.v_ancestor = v_ancestor,
};

void parent_init(struct parent *parent)
{
	parent->ops = &ops;
	snprintf(parent->name, sizeof(parent->name), "Parent-Wilson");
}

void parent_method_work(struct parent *parent)
{
	printf("%s is working now.\n", parent->name);
}
