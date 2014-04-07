#include "strategy.h"

struct strategy_ops strategy_ops = {0}; /* virtual, force derive class implement */

void strategy_init(struct strategy *strategy)
{
	strategy->ops = &strategy_ops;
}

