#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Finite state machine declaration
// State declaration
#define IDLE                 0 // idle state in rx mode
#define M_BROADCAST          1 // broadcast state in tx mode, broadcast to be a master point
#define M_WAIT_BROADCAST_ACK 2 // wait for broadcast ack state in rx mode, wait for the point ack in a specific time window
#define M_WAIT_COMMAND       3 // wait for command state, wait for PC command via UART
#define M_BROADCAST_CANCEL   4 // broadcast cancel state, broadcast to cancel master point

#define S_BROADCAST_ACK      5 // slave mode, send back self physical address
#define S_WAIT_COMMAND       6 // slave mode, wait for command from the master point

// State transition trig
// Used in master mode
int isReqBeMaster = 0 ;// Is PC request the point to be master?
int isTimeout = 0 ;// Is time out?
int isReqCancelMaster = 0 ;// Is request to cancel master?
// Used in slave mode
int isRxBroadcast = 0 ;// Is there a point broadcast to be master?
int isRxBroadcastCancel = 0 ;// Is receive broadcast cancel master?

typedef struct fsmtag
{
	int state; // state
	int timeouttime; // time out time in milliseconds
} Fsm;

// Function prototype
int main ()
{
	fsm f;
	f.state = IDLE;
	f.timeouttime = 0;
	while (1) {
		switch (f.state) {
			case IDLE:
				puts ("IDLE\nWait for isReqBeMaster (1/0) isRxBroadcast (1/0):");
				scanf ("%d% d", & isReqBeMaster, & isRxBroadcast);
				if (isReqBeMaster) {
					f.state = M_BROADCAST;
					break;
				}
				else if (isRxBroadcast) {
					f.state = S_BROADCAST_ACK;
					break;
				}
				else
					break;
			case M_BROADCAST:
				puts ("M_BROADCAST\nBroadcasting...\n");
				f.state = M_WAIT_BROADCAST_ACK;
			case M_WAIT_BROADCAST_ACK:
				puts ("M_WAIT_BROADCAST_ACK\nWaiting for isTimeout (1/0):");
				scanf ("%d", & isTimeout);
				if (isTimeout) {
					f.state = M_WAIT_COMMAND;
					break;
				}
				else
					break;
			case M_WAIT_COMMAND:
				puts ("M_WAIT_COMMAND\nWaiting for isReqCancelMaster (1/0):");
				scanf ("%d", & isReqCancelMaster);
				if (isReqCancelMaster)
				{
					f.state = IDLE;
					break;
				}
				else
					break;
				// Slave mode routine
			case S_BROADCAST_ACK:
				puts ("S_BROADCAST_ACK\nAcking...\n");
				f.state = S_WAIT_COMMAND;
				break;
			case S_WAIT_COMMAND:
				puts ("S_WAIT_COMMAND\nWaiting for isRxBroadcastCancel (1/0):");
				scanf ("%d", & isRxBroadcastCancel);
				if (isRxBroadcastCancel)
				{
					f.state = IDLE;
					break;
				}
				else
					break;
			default:
				puts ("default");
				printf ("%d\n", rand ());
				f.state = IDLE;
		}
	}

	return 0;
}
