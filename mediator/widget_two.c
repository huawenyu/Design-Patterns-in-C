/**
 * widget_two.c  2014-05-18
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
 * Use a mediator when the complexity of object communication begins to hinder object reusability.
    This type of complexity often appears in view instances, though it could really be anywhere.
    1. For example, using mediator to add log file functionality, it works like this:
      - Obj A tells the mediator it needs something done.
      - The mediator sends the message to various client objects.
      - Obj B does the thing Obj A needs, and sends an appropriate message back via the mediator.
      - Meanwhile, Obj C is also sent both messages by the mediator, and logs the results.
          That way, we can get user statistics from the log files.
      - Obj D could be an error checker as well, so that if Obj B responds that Obj A's request is impossible,
          Obj D could be the thing that reports that to the user.
          Errors can now be logged in a different file than regular activity,
          and could use some other means to behave (beeping, whatever) that Obj A shouldn't really concern itself with.

    2. The following code assume that:
      At a highlevel, we have 2 Participants that want to talk so we need to setup a common interface to do so.
      - We create a method call Notify(message); that basically is our channel of communication.
      - To set things up we instantiate a mediator, and then instantiate both participants passing them the mediator.
      - The last step insetup, is to inject/set the mediators participants. In our case we just use simple setters.
      - When its time to communicate, each participant just calls the mediator, passes the message and self as a parameter.
      - Mediator see who contacted them, and then calls the opposite.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "widget_two.h"
#include "mediator.h"

/** send a message, also get the response message */
static char * widget_two_ops_notify(struct participant *participant, char *msg)
{
	struct widget_two *a_widget_two = container_of(participant, typeof(*a_widget_two), participant);
	
	static char response[] = "This is response message from widget_two.";
	_MY_TRACE_STR("widget_two::notify()\n");
	printf("widget_two receive: %s\n", msg);
	return response;
}

static struct participant_ops participant_ops = {
	.notify = widget_two_ops_notify,
};

/** constructor(). */
void widget_two_init(struct widget_two *widget_two, struct mediator *mediator)
{
	_MY_TRACE_STR("widget_two_init()\n");
	memset(widget_two, sizeof(*widget_two), 0);
	participant_init(&widget_two->participant);
	CLASS_OPS_INIT(widget_two->participant.ops, participant_ops);
	widget_two->_mediator = mediator;
}

/** forward to mediator */
char * widget_two_talk(struct widget_two *widget_two, char *msg)
{
	_MY_TRACE_STR("widget_two::talk()\n");
	return mediator_talk(widget_two->_mediator, &widget_two->participant, msg);
}
