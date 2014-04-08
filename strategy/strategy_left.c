
#include <stdio.h>
#include "myobj.h"
#include "strategy_left.h"

static void left_justify(struct strategy *strat, char *line)
{
	printf("left ");
}

static struct strategy_ops left_ops = {
	.justify = left_justify,
};

void strategy_left_init(struct strategy_left *strat)
{
	strategy_init(&strat->strategy);
	CLASS_OPS_INIT(strat->strategy.ops, left_ops);
}
