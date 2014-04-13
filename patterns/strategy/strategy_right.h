#ifndef STRATEGY_RIGHT_H_
#define STRATEGY_RIGHT_H_

#include "strategy.h"

struct strategy_right {
	struct strategy strategy;
};

void strategy_right_init(struct strategy_right *);

#endif /* STRATEGY_RIGHT_H_ */
