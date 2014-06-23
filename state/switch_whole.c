void use_switch ()
{
	cur_state = nxt_state;
	switch (cur_state) {// Analyzing current state event
	case s0: // s0 state
		if (e0_event) {// If e0 event occurs, then the implementation of a0 action, and to maintain the status quo;
			Performing a0 actions;
			// Nxt_state = s0; // Own state number, so you can delete the sentence, in order to improve the operating speed.
		}
		else if (e1_event) {// If e1 event occurs, then the implementation of a1 action, and the state transition to the S1 state;
			Perform a1 actions;
			nxt_state = s1;
		}
		else if (e2_event) {// If e2 Event occurs, then the implementation of a2 actions, s2 and state to state;
			Perform a2 actions;
			nxt_state = s2;
		}
		break;

	case s1: // s1 state
		if (e2_event) {// If e2 Event occurs, then the implementation of a2 actions, s2 and state to state;
			Perform a2 actions;
			nxt_state = s2;
		}
		break;

	case s2: // s2 state
		if (e0_event) {// If e0 event occurs, then the implementation of a0 action, s0 and state to state;
			Performing a0 actions;
			nxt_state = s0;
		}
		break;
	}
}
