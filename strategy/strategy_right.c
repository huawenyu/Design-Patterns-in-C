
#include <stdio.h>
#include "myobj.h"
#include "strategy_right.h"

static void right_justify(struct strategy *strat, char *line)
{
	printf("right ");
}

static struct strategy_ops right_ops = {
	.justify = right_justify,
};

void strategy_right_init(struct strategy_right *strat)
{
	strategy_init(&strat->strategy);
	CLASS_OPS_INIT(strat->strategy.ops, right_ops);
}
