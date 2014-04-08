#include <stdlib.h>
#include "test_bed.h"
#include "strategy_left.h"
#include "strategy_right.h"

static void test_bed_set_strategy(struct test_bed *test, int type)
{
	struct strategy_left *left;
	struct strategy_right *right;

	free(test->strategy_);
	test->strategy_ = 0;
	if (type == Left) {
		left = malloc(sizeof(*left));
		strategy_left_init(left);
		test->strategy_ = &left->strategy;
	}
	else if (type == Right) {
		right = malloc(sizeof(*right));
		strategy_right_init(right);
		test->strategy_ = &right->strategy;
	}
}

static void test_bed_do_it(struct test_bed *test)
{
	strategy_justify(test->strategy_, 0);
}

struct test_bed_ops test_ops = {
	.set_strategy = test_bed_set_strategy,
	.do_it = test_bed_do_it,
};

void test_bed_init(struct test_bed *test)
{
	test->ops = &test_ops;
	test->strategy_ = NULL;
}
