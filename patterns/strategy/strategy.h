#ifndef STRATEGY_H_
#define STRATEGY_H_


struct strategy_ops;
struct strategy {
	struct strategy_ops *ops;
};

struct strategy_ops {
	void (*justify) (struct strategy *, char *line); /* virtual */
};

void strategy_init(struct strategy *);

static inline
void strategy_justify(struct strategy *strat, char *line)
{
	strat->ops->justify(strat, line);
}

#endif /* STRATEGY_H_ */
