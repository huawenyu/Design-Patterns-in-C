
#include <stdio.h>
#include <myobj.h>
#include "grandson.h"

static void grandson_v_override_who(struct parent *parent)
{
	printf("[virtual-override] I'm %s.\n", parent->name);
}

static struct parent_ops parent_ops = {
	.v_override_who = grandson_v_override_who,
};

static struct child_ops child_ops = {0};

void grandson_init(struct grandson *grandson)
{
	child_init(&grandson->child);
	CLASS_OPS_INIT(grandson->child.parent.ops, parent_ops);
	CLASS_OPS_INIT(grandson->child.ops, child_ops);
	snprintf(grandson->child.parent.name, sizeof(grandson->child.parent.name),
		"Grandson-Andy");
}

