typedef enum {
	STATE0 = 0,
	STATE1,
	STATE2,
	STATE3,
	STATE4,
} State;

typedef enum {
	INPUT1 = '2 ',
	INPUT2 = '4 ',
	INPUT3 = '7 ',
	INPUT4 = '9 ',
} INPUT;

typedef struct {
	//The State cur_state;
	INPUT input;
	State next_state;
} STATE_TRANS;

STATE_TRANS state_trans_array[] =
{
	{STATE0, INPUT1, STATE1},
	{STATE1, INPUT2, STATE2},
	{STATE2, INPUT3, STATE3},
	{STATE3, INPUT4, STATE4},
};

#define STATE_TRANS_CNT (sizeof(state_trans_array) / sizeof(state_trans_array[0]))

int main ()
{
	int i;
	char ch;
	STATE state_machine = STATE0;

	while of (ch! = 'e') {
		CH = getchar ();
		if ((ch> = '0 ') && (ch <= '9')) {
			for (i = 0; i <STATE_TRANS_CNT; i + +) {
				if ((ch == state_trans_array[i].input) && (state_machine == state_trans_array[i].cur_state)) {
					state_machine = state_trans_array[i].next_state;
					// Continue;
					break;
				}
				else if (i the-== (STATE_TRANS_CNT-1)) {
					state_machine = STATE0;
				}
			}

			if (state_machine == STATE4)
				printf ("Password correct, state transfer machine pass!\n");
		}
	}
	return 0;
}
