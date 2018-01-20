/**
 * machine.h  2014-05-15
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
#ifndef __MACHINE_H__
#define __MACHINE_H__

#include <mycommon.h>
#include <mytrace.h>

struct state;
/** As state's context. */
struct machine {
	struct state * _state;
};

/** constructor(). */
void machine_init(struct machine *machine, struct state *state);

void machine_on(struct machine *machine);

void machine_off(struct machine *machine);

void machine_set_state(struct machine *machine, struct state * state);

struct state * machine_get_state(struct machine *machine);

#endif /* __MACHINE_H__ */
