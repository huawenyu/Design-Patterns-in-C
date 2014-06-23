#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main ()
{
	char ch;
	STATE current_state = STATE0;
	while (1)
	{
		printf ("please input number to decode:");
		while ((ch = getchar ())! = '\n') {
			if ((ch <'0 ') | | (ch> '9')) {
				printf ("not number, please input again! \n");
				break;
			}

			switch (the current_state) {
				case STATE0:
					if (ch == '2 ') current_state = STATE1;
					break;
				case STATE1:
					if (ch == '4 ') current_state = STATE2;
					break;
				case STATE2:
					if (ch == '7 ') current_state = STATE3;
					break;
				case STATE3:
					if (ch == '9 ') current_state = STATE4;
					break;
				default:
					current_state = STATE0;
					break;
			}
		}

		if (current_state == STATE4) {
			printf ("corrent, lock is open!\n");
			current_state = STATE0;
		}
		else {
			printf ("wrong, unlocked!\n");
			current_state = STATE0;
		}
	}

	return 0;
}
