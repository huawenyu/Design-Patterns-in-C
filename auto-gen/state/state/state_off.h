/**
 * state_off.h  2014-05-15
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
#ifndef __STATE_OFF_H__
#define __STATE_OFF_H__

#include <mycommon.h>
#include <mytrace.h>

#include "machine.h"
		
#include "state.h"

/** ops's transition */
struct state_off {
	struct state state;
};

/** constructor(). */
void state_off_init(struct state_off *state_off);

#endif /* __STATE_OFF_H__ */