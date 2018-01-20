/**
 * state_off.c  2014-05-15
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
#include "state_off.h"
#include "state_on.h"

/** called by free(): put resources, forward to super. */
static void state_off_ops__destructor(struct state *state)
{
	_MY_TRACE_STR("state_off::_destructor()\n");
	CLASS_SUPER(state, _destructor);
}
/** free memory after call destructor(). */
static void state_off_ops_free(struct state *state)
{
	struct state_off *a_state_off = container_of(state, typeof(*a_state_off), state);
	state__destructor(state);
	_MY_TRACE_STR("state_off::free()\n");
	free(a_state_off);
}
/** forward declare machine */
static void state_off_ops_on(struct state *state, struct machine *fsm)
{
	struct state_on *on;

	_MY_TRACE_STR("state_off::on()\n");

	on = malloc(sizeof(*on));
	state_on_init(on);
	machine_set_state(fsm, &on->state);

	state_free(state);
}

static struct state_ops state_ops = {
	._destructor = state_off_ops__destructor,
	.free = state_off_ops_free,
	.on = state_off_ops_on,
};

/** constructor(). */
void state_off_init(struct state_off *state_off)
{
	_MY_TRACE_STR("state_off_init(1)\n");
	memset(state_off, sizeof(*state_off), 0);
	state_init(&state_off->state);
	CLASS_OPS_INIT_SUPER(state_off->state.ops, state_ops);
}
