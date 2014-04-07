#include "chain_handle1.h"
#include "chain_handle2.h"
#include "chain_handle3.h"

static int test()
{
	int i;

	struct chain_handle1 root;
	struct chain_handle2 two;
	struct chain_handle3 thr;

	chain_handle1_init(&root);
	chain_handle2_init(&two);
	chain_handle3_init(&thr);

	chain_base_add(&root.super, &two.super);
	chain_base_add(&root.super, &thr.super);
	thr.super.next = &root.super;

	for (i = 1; i < 10; i++) {
		chain_base_handle(&root.super, i);
	}
	return 0;
}

void chain_of_responsibility_test()
{
	my_test_suite_add(test, "chain of responsibility test");
}
