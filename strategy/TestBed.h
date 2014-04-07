#ifndef TESTBED_H_
#define TESTBED_H_

struct test_bed_ops;
struct test_bed {
	struct test_bed_ops *ops;
	struct strategy *strategy_;
};


enum strategy_type {
	Dummy, Left, Right,
};

struct test_bed_ops {
	void (*set_strategy) (struct test_bed *, int type);
	void (*do_it) (struct test_bed *);
};

void test_bed_init(struct test_bed *);

#endif /* TESTBED_H_ */
