
#include <stdio.h>
#include <stdlib.h>

#include <test_suite.h>
#include "grandgirl.h"
#include "grandson.h"

static int test_inheritance(char *output, size_t sz)
{
	struct parent parent;
	struct child child;
	struct grandgirl grandgirl;
	struct grandson grandson;

	parent_init(&parent);
	child_init(&child);
	grandgirl_init(&grandgirl);
	grandson_init(&grandson);

	printf("parent::who()\n");
	parent_v_override_who(&parent);
	printf("child::who()\n");
	parent_v_override_who(&child.parent);
	printf("grandgirl::who()\n");
	parent_v_override_who(&grandgirl.child.parent);
	printf("grandson::who()\n");
	parent_v_override_who(&grandson.child.parent);

	printf("parent::ancestor()\n");
	parent_v_ancestor(&parent);
	printf("child::ancestor()\n");
	parent_v_ancestor(&child.parent);
	printf("grandgirl::ancestor()\n");
	parent_v_ancestor(&grandgirl.child.parent);
	printf("grandson::ancestor()\n");
	parent_v_ancestor(&grandson.child.parent);

	printf("child::child_right()\n");
	child_v_child_right(&child, "watch movie");
	printf("grandgirl::child_right()\n");
	child_v_child_right(&grandgirl.child, "watch cartoon");
	printf("grandson::child_right()\n");
	child_v_child_right(&grandson.child, "watch cartoon");

	return 0;
}

void inheritance_test(void);
void inheritance_test(void)
{
	my_test_suite_add(test_inheritance, "Inheritance: Parent-Child-Grand");
}
