/**
 * state.c  2014-05-15
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C *
 * 
 * There are really two key aspects to consider in working with the state
    pattern: enumeration and transition. Enumeration simply means identifying
    the set of possible states (e.g. days of the week), or more abstractly the
    types of states (i.e. meta states) such as starting, ending, and in between
    for a workflow engine.Transition means deciding how to model movement
    between states where this is typically either done by capturing all
    possible transitions in a tabular representation (i.e. Finite State
    Machine) or make each state know its possible "transitions" to other
    states.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "state.h"

/** called by free(): put resources, forward to super. */
static void state_ops__destructor(struct state *state)
{
	_MY_TRACE_STR("state::_destructor()\n");
}
/** free memory after call destructor(). */
static void state_ops_free(struct state *state)
{
	_MY_TRACE_STR("state::free()\n");
}
/** forward declare machine */
static void state_ops_on(struct state *state, struct machine *fsm)
{
	_MY_TRACE_STR("state::on() do-nothing ...\n");
}
/** forward declare machine */
static void state_ops_off(struct state *state, struct machine *fsm)
{
	_MY_TRACE_STR("state::off() do-nothing ...\n");
}
static struct state_ops state_ops = {
	._destructor = state_ops__destructor,
	.free = state_ops_free,
	.on = state_ops_on,
	.off = state_ops_off,
};

/** constructor(). */
void state_init(struct state *state)
{
	_MY_TRACE_STR("state_init(1)\n");
	memset(state, sizeof(*state), 0);
	state->ops = &state_ops;
}
