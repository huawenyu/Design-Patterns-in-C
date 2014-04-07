#ifndef RIGHTSTRATEGY_H_
#define STRATEGY_LEFT_H_

#include "strategy.h"

struct strategy_left {
	struct strategy strategy;
};

void strategy_left_malloc(struct strategy_left *);
void strategy_left_init(struct strategy_left *);

#endif /* RIGHTSTRATEGY_H_ */
