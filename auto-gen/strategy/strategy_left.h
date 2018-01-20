#ifndef STRATEGY_LEFT_H_
#define STRATEGY_LEFT_H_

#include "strategy.h"

struct strategy_left {
	struct strategy strategy;
};

void strategy_left_init(struct strategy_left *);

#endif /* STRATEGY_LEFT_H_ */
