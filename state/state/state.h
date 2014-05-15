/**
 * state.h  2014-05-15
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
#ifndef __STATE_H__
#define __STATE_H__

#include <mycommon.h>
#include <mytrace.h>

struct machine;
struct state_ops;
/** ops's transition */
struct state {
	struct state_ops *ops;
};
struct state_ops {
	void (*_destructor)(struct state *); /** called by free(): put resources, forward to super. */
	void (*free)(struct state *); /** free memory after call destructor(). */
	void (*on)(struct state *, struct machine *fsm); /** forward declare machine */
	void (*off)(struct state *, struct machine *fsm); /** forward declare machine */
	struct state_ops *__super;
};

/** constructor(). */
void state_init(struct state *state);

/** called by free(): put resources, forward to super. */
static inline void state__destructor(struct state *state)
{
	state->ops->_destructor(state);
}
/** free memory after call destructor(). */
static inline void state_free(struct state *state)
{
	state->ops->free(state);
}
/** forward declare machine */
static inline void state_on(struct state *state, struct machine *fsm)
{
	state->ops->on(state, fsm);
}
/** forward declare machine */
static inline void state_off(struct state *state, struct machine *fsm)
{
	state->ops->off(state, fsm);
}

#endif /* __STATE_H__ */
