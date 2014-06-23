// E0 event occurs, the function to be executed
void e0_event_function (int * nxt_state)
{
	int cur_state;

	cur_state = * nxt_state;
	switch (cur_state)
	{
		case s0: // observation in Table 1, when the in e0 event occurs, s1 place is empty
		case s2:
			Performing a0 actions;
			* Nxt_state = s0;
	}
}

// E1 event occurs, the function to be executed
void e1_event_function (int * nxt_state)
{
	int cur_state;

	cur_state = * nxt_state;
	switch (cur_state)
	{
		case s0: // observed in Table 1, e1 incident, s1 and s2 at the empty
			Perform a1 actions;
			* Nxt_state = s1;
	}
}

// E2 event occurs, the function to be executed
void e2_event_function (int * nxt_state)
{
	int cur_state;

	cur_state = * nxt_state;
	switch (cur_state)
	{
		case s0: // Observation Table 1, in the occurrence of event e2, s2 at the empty
		case s1:
			Perform a2 actions;
			* Nxt_state = s2;
	}
}
