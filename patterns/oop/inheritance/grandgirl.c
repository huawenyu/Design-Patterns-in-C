
#include <stdio.h>
#include <myobj.h>
#include "grandgirl.h"

static void grandgirl_v_override_who(struct parent *parent)
{
	printf("[virtual-override] I'm %s.\n", parent->name);
}

static struct parent_ops parent_ops = {
	.v_override_who = grandgirl_v_override_who,
};

static struct child_ops child_ops = {0};

void grandgirl_init(struct grandgirl *grandgirl)
{
	child_init(&grandgirl->child);
	CLASS_OPS_INIT(grandgirl->child.parent.ops, parent_ops);
	CLASS_OPS_INIT(grandgirl->child.ops, child_ops);
	snprintf(grandgirl->child.parent.name, sizeof(grandgirl->child.parent.name),
		"GrandGirl-Emma");
}

